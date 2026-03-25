#!/usr/bin/env python3
"""LIMINAL Serial-to-WebSocket Bridge
pip install pyserial websockets
python bridge.py
"""
import asyncio, json, time, argparse, logging
from collections import defaultdict
import serial, serial.tools.list_ports, websockets

logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s")
log = logging.getLogger("liminal")
readings = {}
clients = set()
stats = defaultdict(int)

def find_heltec_ports():
    ports = []
    for p in serial.tools.list_ports.comports():
        desc = (p.description or "").lower()
        vid = p.vid or 0
        if vid in (0x10C4, 0x1A86) or "cp210" in desc or "ch910" in desc:
            ports.append(p.device)
            log.info(f"Found Heltec: {p.device} ({p.description})")
    return ports

def parse_line(line):
    if line.startswith("LIMINAL:BOOT:"):
        log.info(f"Node {line.split(':')[2]} booted"); return None
    if not line.startswith("LIMINAL:DATA:"): return None
    try:
        data = json.loads(line[len("LIMINAL:DATA:"):])
        if {"node","peer","rssi","snr"}.issubset(data.keys()): return data
    except json.JSONDecodeError: pass
    return None

async def serial_reader(port, baud):
    log.info(f"Opening {port} at {baud} baud")
    try: ser = serial.Serial(port, baud, timeout=0.1)
    except serial.SerialException as e: log.error(f"Cannot open {port}: {e}"); return
    buf = ""
    while True:
        try:
            raw = ser.read(ser.in_waiting or 1)
            if raw:
                buf += raw.decode("utf-8", errors="ignore")
                while "\n" in buf:
                    line, buf = buf.split("\n", 1)
                    line = line.strip()
                    if not line: continue
                    data = parse_line(line)
                    if data:
                        a, b = min(data["node"], data["peer"]), max(data["node"], data["peer"])
                        key = f"{a}-{b}"
                        readings[key] = {"from":data["node"],"to":data["peer"],"rssi":data["rssi"],"snr":data["snr"],"seq":data.get("seq",0),"time":time.time()}
                        stats["packets"] += 1
                        msg = json.dumps({"type":"reading","pair":key,**readings[key]})
                        if clients: await asyncio.gather(*[c.send(msg) for c in clients], return_exceptions=True)
        except serial.SerialException as e: log.error(f"Serial error: {e}"); break
        await asyncio.sleep(0.01)

async def ws_handler(websocket, path=None):
    clients.add(websocket)
    log.info(f"Client connected ({len(clients)} total)")
    try:
        await websocket.send(json.dumps({"type":"snapshot","readings":readings,"nodes":4}))
        async for msg in websocket:
            cmd = json.loads(msg) if msg else {}
            if cmd.get("type") == "ping": await websocket.send(json.dumps({"type":"pong"}))
    except websockets.exceptions.ConnectionClosed: pass
    finally: clients.discard(websocket); log.info(f"Client disconnected ({len(clients)} total)")

async def status_printer():
    while True:
        await asyncio.sleep(10)
        active = sum(1 for r in readings.values() if time.time() - r["time"] < 5)
        log.info(f"Active: {active}/6 | Packets: {stats['packets']} | Clients: {len(clients)}")

async def main(args):
    ports = args.ports or find_heltec_ports()
    serial_tasks = [serial_reader(p, args.baud) for p in ports]
    ws_server = await websockets.serve(ws_handler, "0.0.0.0", args.ws_port)
    log.info(f"LIMINAL Bridge | Serial: {ports or '(waiting)'} | WS: ws://localhost:{args.ws_port}")
    await asyncio.gather(*serial_tasks, status_printer(), return_exceptions=True)

if __name__ == "__main__":
    p = argparse.ArgumentParser()
    p.add_argument("--ports", nargs="+")
    p.add_argument("--baud", type=int, default=115200)
    p.add_argument("--ws-port", type=int, default=8765)
    asyncio.run(main(p.parse_args()))