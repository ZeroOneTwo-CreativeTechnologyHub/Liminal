```
┌──────────────────────────────────────────────┐
│░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░│
│░░ ██╗░░░░░██╗███╗░░░███╗██╗███╗░░██╗░█████╗░░│
│░░ ██║░░░░░██║████╗░████║██║████╗░██║██╔══██╗░│
│░░ ██║░░░░░██║██╔████╔██║██║██╔██╗██║███████║░│
│░░ ██║░░░░░██║██║╚██╔╝██║██║██║╚████║██╔══██║░│
│░░ ███████╗██║██║░╚═╝░██║██║██║░╚███║██║░░██║░│
│░░ ╚══════╝╚═╝╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░╚═╝░│
│░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░│
│░░ ██╗░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░│
│░░ ██║░░░░░LoRa Radio-Space Sensing░░░░░░░░░░░│
│░░ ██║░░░░░& Visualisation░░░░░░░░░░░░░░░░░░░░│
│░░ ███████╗░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░│
│░░ ╚══════╝░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░│
│░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░│
├──────────────────────────────────────────────┤
│  See the invisible. Walk through radio.      │
│  No internet, no cloud, no tracking.         │
└──────────────────────────────────────────────┘
```

## What is this?

LIMINAL turns 4 cheap LoRa radio boards into a **real-time sensor that maps the invisible electromagnetic space** of a room — and visualises how human bodies distort it just by being there.

Most LoRa projects treat radio as a transparent pipe: send a message from A to B. LIMINAL inverts this. **The radio link *is* the data.** Four nodes continuously ping each other, and by watching how signal strength changes across all 6 node-to-node paths, the system builds a living topographic map of radio energy flowing through physical space.

Walk between two nodes and the signal attenuates. The mesh dips. Step away and it recovers. You're watching your own body cast a shadow in a spectrum you've never been able to see.

```
    [A] ─────────────────── [B]
     │ \                  / │
     │   \   6 signal   /   │        Walk through the space.
     │     \  paths   /     │        Watch the mesh ripple.
     │       \      /       │
     │         \  /         │        Your body is distorting
     │          \/          │        an invisible landscape
     │          /\          │        that has always been there.
     │        /    \        │
     │      /        \      │
     │    /            \    │
     │  /                \  │
    [D] ─────────────────── [C]
```

> **Try the live demo →** [zeroonetwo-creativetechnologyhub.github.io/Liminal](https://zeroonetwo-creativetechnologyhub.github.io/Liminal/)
> Move your cursor to simulate a body in radio space. No hardware needed.

---

## How it works

```
┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐
│ Heltec A │  │ Heltec B │  │ Heltec C │  │ Heltec D │
│ (Node 0) │  │ (Node 1) │  │ (Node 2) │  │ (Node 3) │
└─────┬────┘  └──────────┘  └──────────┘  └──────────┘
      │ USB      battery       battery       battery
      │
      │  Each node pings in a TDMA cycle (200ms slots).
      │  Every node hears every other node.
      │  One USB connection captures all 6 pair readings.
      │
      ▼
┌───────────────────────────────────────────────────────┐
│  bridge.py                                            │
│  Reads RSSI + SNR from serial → serves via WebSocket  │
└──────────────────────────┬────────────────────────────┘
                           │ ws://localhost:8765
                           ▼
┌───────────────────────────────────────────────────────┐
│  visualiser (P5.js)                                   │
│  6 signal values → deformable mesh → living topology  │
│  Auto-connects to bridge or runs in simulation mode   │
└───────────────────────────────────────────────────────┘
```

4 nodes = **6 unique signal paths**. Each path reports RSSI (signal strength) and SNR (signal-to-noise ratio). Together they form a crude but readable **radio tomography** of the space — enough to sense presence, movement, and even rough position of people walking through.

---

## Hardware

| Item | Qty | Notes |
|---|---|---|
| **Heltec WiFi LoRa 32 V2** | 4 | ESP32 + SX1276 LoRa + 0.96" OLED |
| USB-C cables | 1–4 | At least 1 to connect a node to your laptop |
| USB power banks | 3 | For the untethered nodes |
| LoRa antennas | 4 | **⚠ Always attach before powering on** |

Place nodes at the corners of your sensing area, 3–15 metres apart, at roughly waist height (~1m). Each node's OLED displays live RSSI to its three peers — use this to check placement before running the visualiser.

---

## Quick start

### Flash the boards (browser — no tools needed)

> Requires **Chrome** or **Edge** on desktop.

1. Open the **[LIMINAL web flasher](https://zeroonetwo-creativetechnologyhub.github.io/Liminal/)**
2. Plug in a Heltec V2 via USB-C
3. Click **Flash Node 0** (or 1, 2, 3)
4. Repeat for each board

First time? Hold the **BOOT** button on the board while plugging in. If the board isn't detected, install [CP210x USB drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers).

### Or build from source

```bash
git clone https://github.com/ZeroOneTwo-CreativeTechnologyHub/Liminal.git
cd Liminal

# Flash each node (change env name for each board)
pio run -e node0 -t upload
pio run -e node1 -t upload
pio run -e node2 -t upload
pio run -e node3 -t upload
```

### Run the visualiser

```bash
# Install bridge dependencies
pip install pyserial websockets

# Plug at least 1 flashed node into USB, then:
python bridge/bridge.py

# Open the visualiser in your browser
open visualiser/index.html
```

The visualiser auto-connects to the bridge at `ws://localhost:8765`. If the bridge isn't running, it falls back to mouse-based simulation mode.

---

## Project structure

```
Liminal/
│
├── src/
│   └── main.cpp                 ← Firmware (TDMA ping cycle, RSSI logging, OLED display)
│
├── platformio.ini               ← Build config with 4 environments (node0–node3)
│
├── bridge/
│   ├── bridge.py                ← Serial → WebSocket bridge (Python)
│   └── requirements.txt
│
├── visualiser/
│   └── index.html               ← Standalone P5.js visualiser (connects to bridge)
│
├── docs/
│   ├── index.html               ← GitHub Pages site (flasher + demo + serial monitor)
│   └── firmware/
│       ├── node0/               ← Pre-built binaries + ESP Web Tools manifest
│       ├── node1/
│       ├── node2/
│       └── node3/
│
├── .github/
│   └── workflows/
│       └── build.yml            ← CI: compiles firmware, commits binaries, updates Pages
│
├── LICENSE                      ← MIT
└── README.md                    ← You are here
```

---

## Frequency

The firmware defaults to **868 MHz** (EU/UK). If you're in the US, Australia, or another 915 MHz region, change this line in `platformio.ini`:

```ini
-DFREQUENCY=915E6
```

Then rebuild and reflash all 4 nodes.

---

## The serial protocol

Each node outputs newline-delimited JSON at 115200 baud:

```
LIMINAL:BOOT:0
LIMINAL:DATA:{"node":0,"peer":1,"rssi":-42.0,"snr":9.5,"seq":127,"t":45230}
LIMINAL:DATA:{"node":0,"peer":2,"rssi":-58.0,"snr":6.2,"seq":84,"t":45430}
LIMINAL:DATA:{"node":0,"peer":3,"rssi":-51.0,"snr":7.8,"seq":91,"t":45630}
```

The GitHub Pages site includes a built-in **serial monitor** — plug in a board, open the Serial tab, and you can see the raw data stream directly in the browser.

---

## Extending LIMINAL

This is a starting point, not a finished product. Some directions to take it:

**Sonification** — Map each of the 6 signal pairs to a Tone.js oscillator. Signal attenuation becomes pitch shift or filter cutoff. Human movement becomes involuntary music.

**Projection mapping** — Mount a projector above or below the sensing area, run the visualiser fullscreen, and calibrate node positions to physical space. The radio topology overlays the room itself.

**Recording & playback** — Add CSV logging to bridge.py. Capture a performance, exhibition, or just a day of foot traffic. Play it back through the visualiser later.

**Occupancy counting** — Train a simple classifier on RSSI patterns. With 6 signal paths, you can distinguish 0, 1, 2+ people with reasonable accuracy.

**Multi-room** — Chain rooms by sharing border nodes. Node C in Room 1 becomes Node A in Room 2.

---

## Context

LIMINAL was built at [Zero One Two Creative Technology Hub](https://github.com/ZeroOneTwo-CreativeTechnologyHub) as an experiment in making invisible infrastructure legible. It sits somewhere between RF tomography (usually done with expensive lab equipment), interactive art installation, and environmental sensing — using hardware that costs under £20 per node.

The project is designed to be accessible to artists, designers, and creative technologists who may not have deep embedded systems experience. Flash from the browser, plug in, watch the mesh breathe.

---

## Licence

MIT — use it, remix it, exhibit it, teach with it.
