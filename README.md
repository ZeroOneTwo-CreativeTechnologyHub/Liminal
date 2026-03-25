# LIMINAL

**LoRa Radio-Space Sensing & Visualisation**

> Turn 4 Heltec V2 LoRa nodes into a real-time radio topology sensor
> that visualises the invisible electromagnetic architecture of physical space.

## Quick Start

### Option A — Web Flasher (no tools needed)

1. Push this repo to GitHub
2. Go to **Settings → Pages → Source: "Deploy from a branch" → Branch: main → Folder: /docs → Save**
3. Wait ~60s, then open `https://YOUR_USER.github.io/liminal/` in Chrome
4. Connect a Heltec WiFi LoRa 32 V2 via USB
5. Click "Flash Node 0" / 1 / 2 / 3
6. (Flash buttons work after the CI Action builds firmware — trigger it from the Actions tab)

### Option B — Build from source

```bash
git clone https://github.com/YOUR_USER/liminal.git
cd liminal
pio run -e node0 -t upload  # repeat for node1, node2, node3
```

### Run the visualiser

```bash
pip install pyserial websockets
python bridge/bridge.py
open visualiser/index.html
```

## How It Works

4 nodes ping each other in a TDMA cycle. RSSI/SNR for all 6 pairs
are streamed to a P5.js visualiser that renders a living, deformable mesh.
When people walk through the sensing area, signals attenuate and the mesh ripples.

## Structure

```
liminal/
├── src/main.cpp              Heltec V2 firmware
├── platformio.ini            Build config (4 node envs)
├── bridge/bridge.py          Serial → WebSocket bridge
├── visualiser/index.html     Standalone P5.js visualiser
├── docs/                     GitHub Pages site + web flasher
└── .github/workflows/        CI: compile → deploy
```

## Hardware

- 4 × Heltec WiFi LoRa 32 V2
- USB-C cables (1 minimum for bridge)
- 3 × USB power banks
- LoRa antennas (always attach before powering on)

## Licence

MIT