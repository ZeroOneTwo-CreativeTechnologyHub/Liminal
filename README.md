
```
┌────────────────────────────────┐
│ LIMINAL                        │
│                                │
│ 1: -74dBm ████░░░░  9.5dB     │
│ 2: -42dBm ███████░ 13.0dB     │
│ 3: -37dBm ████████ 12.8dB     │
│                                │
│ LoRa Radio-Space Sensing       │
│ & Visualisation                │
└────────────────────────────────┘
  See the invisible.
  Walk through radio.
```

## What is this?

LIMINAL turns 4 cheap LoRa radio boards into a **real-time sensor that maps the invisible electromagnetic space** of a room — and visualises how human bodies distort it just by being there.

Most LoRa projects treat radio as a transparent pipe: send a message from A to B. LIMINAL inverts this. **The radio link *is* the data.** Four nodes continuously ping each other, and by watching how signal strength changes across all 6 node-to-node paths, the system builds a living topographic map of radio energy flowing through physical space.

Walk between two nodes and the signal attenuates. The mesh dips. Step away and it recovers. You're watching your own body cast a shadow in a spectrum you've never been able to see.

```
    [A] ─────────────────── [B]
     │ \                  / │
     │   \   6 signal   /   │
     │     \  paths   /     │       4 nodes = 6 signal paths
     │       \      /       │       Each path = 1 RSSI reading
     │        [  ]         │       Together = radio topology map
     │       /      \       │
     │     /          \     │       Walk through the space.
     │   /              \   │       Watch the mesh ripple.
     │ /                  \ │
    [D] ─────────────────── [C]
```

> **Try the live demo →** [zeroonetwo-creativetechnologyhub.github.io/Liminal](https://zeroonetwo-creativetechnologyhub.github.io/Liminal/)

---

## What you need

| Item | Qty | ~Cost | Notes |
|---|---|---|---|
| **Heltec WiFi LoRa 32 V3** | 4 | £18 each | ESP32-S3 + SX1262 + OLED. [Buy here](https://heltec.org/project/wifi-lora-32-v3/) |
| USB-C cable | 1 | — | A good data cable (not charge-only) |
| USB power banks | 3 | — | To power the untethered nodes |
| A laptop | 1 | — | Running Chrome or Edge, with Python 3 installed |

The LoRa antennas come included with the boards. **Always attach them before powering on.**

---

## Get it running in 4 steps

### Step 1 — Flash the boards

No software to install. Open this link in **Chrome** or **Edge** on a desktop/laptop:

> **[zeroonetwo-creativetechnologyhub.github.io/Liminal](https://zeroonetwo-creativetechnologyhub.github.io/Liminal/)**

For each of your 4 boards:

1. Plug the board into your laptop via USB-C
2. Click **Flash Node 0** (then Node 1, Node 2, Node 3 — one board per ID)
3. Select the serial port when prompted
4. Wait for "Installation complete"
5. Unplug and set aside. Repeat with the next board.

**If the board isn't detected:** hold the **BOOT** button while plugging in USB, then try again.

Each board's OLED screen will show `LIMINAL [0] READY` (or 1, 2, 3) when it boots. If you see dBm readings appearing for other nodes, the radios are working.

### Step 2 — Position the nodes

```
    [A]                          [B]
     ●───────── 5-10m ───────────●
     │                            │
     │    Place nodes at the      │
   5-10m  corners of your space  5-10m
     │    at waist height (~1m)   │
     │                            │
     ●───────── 5-10m ───────────●
    [D]                          [C]
```

- **Node 0** stays plugged into your laptop (it's the bridge to the visualiser)
- **Nodes 1, 2, 3** run on USB power banks
- Keep line of sight between most pairs — avoid thick concrete walls
- Each node's OLED shows live signal strength to its peers

### Step 3 — Start the bridge

The bridge reads radio data from Node 0 over USB and sends it to the visualiser. You need Python 3 (pre-installed on macOS; [download for Windows](https://www.python.org/downloads/)).

Open a terminal and run:

```bash
pip3 install pyserial websockets
```

Then download the two bridge files from this repo ([bridge.py](https://raw.githubusercontent.com/ZeroOneTwo-CreativeTechnologyHub/Liminal/main/bridge/bridge.py) and [requirements.txt](https://raw.githubusercontent.com/ZeroOneTwo-CreativeTechnologyHub/Liminal/main/bridge/requirements.txt)), or clone the repo:

```bash
git clone https://github.com/ZeroOneTwo-CreativeTechnologyHub/Liminal.git
cd Liminal
```

Run the bridge:

```bash
python3 bridge/bridge.py
```

You should see:

```
Found Heltec: /dev/cu.usbserial-0001
LIMINAL Bridge | Serial: [...] | WS: ws://localhost:8765
Active: 3/6 | Packets: 30 | Clients: 0
```

Leave this running.

### Step 4 — Open the visualiser

Open `visualiser/index.html` in Chrome. On macOS you can run:

```bash
open visualiser/index.html
```

Or just double-click the file in Finder.

The top-left should say **LIVE — receiving from nodes**. The top-right shows all 6 signal pairs with live dBm readings.

**Now walk slowly between the nodes** and watch the mesh respond to your body.

---

## Tuning

The mesh responds to *changes* in signal strength. If it looks too flat, adjust these values at the top of `visualiser/index.html`:

| Variable | Default | What it does |
|---|---|---|
| `RSSI_MIN` | -110 | Weakest signal to visualise. Lower = more sensitive |
| `RSSI_MAX` | -25 | Strongest signal |
| `PATH_WIDTH` | 220 | How wide each signal path affects the mesh |
| `MESH_GAIN` | 28 | How dramatically signal changes deform the mesh |

**Flat mesh?** Increase `MESH_GAIN`. Move nodes further apart.

**Weak paths invisible?** Lower `RSSI_MIN`.

**Too noisy?** Reduce `PATH_WIDTH` or `MESH_GAIN`.

---

## How it works (technical)

Each node transmits a short LoRa ping in a TDMA cycle — Node 0 transmits, then Node 1, then 2, then 3, then back to 0. Each slot is 250ms, so a full cycle takes 1 second. When a node receives a ping from another node, it logs the RSSI (signal strength) and SNR (signal-to-noise ratio) and outputs it as JSON over USB serial.

Node 0 hears the other 3 nodes directly. That gives us 3 of the 6 pairs. The bridge collates readings from all connected nodes — if you only connect Node 0, you get 3 pairs. The visualiser still works with partial data, but for all 6 pairs you can connect additional nodes or infer the missing pairs.

The visualiser maps each signal path to a corridor on a 2D mesh grid. When RSSI drops (signal attenuated), the mesh dips along that corridor. When it recovers, the mesh springs back. The physics simulation uses spring/damping to create smooth, organic movement.

---

## Serial protocol

Each node outputs at 115200 baud:

```
LIMINAL:BOOT:0
LIMINAL:DATA:{"node":0,"peer":1,"rssi":-74.0,"snr":9.5,"seq":127,"t":45230}
LIMINAL:DATA:{"node":0,"peer":2,"rssi":-42.0,"snr":13.0,"seq":84,"t":45430}
```

---

## Project structure

```
Liminal/
├── docs/                        ← GitHub Pages site
│   ├── index.html               ← Web flasher + live demo
│   └── firmware/node0-3/        ← Pre-built binaries
├── bridge/
│   └── bridge.py                ← Serial → WebSocket bridge
├── visualiser/
│   └── index.html               ← P5.js visualiser
├── src/
│   └── main.cpp                 ← Firmware source (for developers)
├── platformio.ini               ← PlatformIO config (for developers)
├── build_and_deploy.sh          ← Rebuilds firmware binaries (for developers)
└── README.md
```

---

## Extending LIMINAL

**Sonification** — Map 6 signal pairs to oscillators. Movement becomes music.

**Projection mapping** — Floor-mount a projector, overlay the mesh on the physical space.

**Recording** — Add CSV logging to bridge.py. Capture and replay sessions.

**Occupancy counting** — Classify RSSI patterns to count people.

**Multi-room** — Share border nodes between adjacent spaces.

---

## For developers

If you want to modify the firmware, you'll need [PlatformIO](https://platformio.org/). Clone the repo, open in VS Code with the PlatformIO extension, and:

```bash
pio run -e node0 -t upload   # flash each board
pio device monitor            # watch serial output
./build_and_deploy.sh         # rebuild web flasher binaries
git push                      # update GitHub Pages
```

The firmware uses [RadioLib](https://github.com/jgromes/RadioLib) for SX1262 communication and the [ThingPulse SSD1306](https://github.com/ThingPulse/esp8266-oled-ssd1306) library for the OLED.

**Frequency:** defaults to 868 MHz (EU/UK). Change `-DFREQUENCY=915.0` in `platformio.ini` for US/AU.

---

## Troubleshooting

| Problem | Solution |
|---|---|
| Web flasher doesn't detect board | Hold **BOOT** while plugging in USB. Try a different cable. Use Chrome/Edge. |
| OLED shows `--` for all peers | Check antennas are attached. Make sure each board has a different Node ID (0–3). |
| Bridge says "cannot open port" | Close any serial monitors first. Only one thing can use the USB port at a time. |
| Visualiser says "connecting..." | Make sure `bridge.py` is running in another terminal window. |
| Mesh is flat / no response to movement | Increase `MESH_GAIN`. Move nodes further apart (5–10m). Walk slowly. |
| Bridge shows 3/6 pairs not 6/6 | Normal with 1 USB node — it only hears 3 peers. Connect more nodes for all 6. |

---

## Context

Built at [Zero One Two Creative Technology Hub](https://github.com/ZeroOneTwo-CreativeTechnologyHub) as an experiment in making invisible infrastructure legible. Sits between RF tomography, interactive art, and environmental sensing — using hardware under £20 per node.

**Licence:** MIT — use it, remix it, exhibit it, teach with it.