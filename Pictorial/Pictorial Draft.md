# LIMINAL: Sensing the Body Through Radio Space

## TEI '27 Pictorial Draft: "The Body in Space"

**Format:** Max 12 pages (excl. references) · Images primary, text as scaffolding · Double-blind · Abstract ≤150 words · Deadline: July 31st AoE

---

### PAGE 1: Title page

**Title:** LIMINAL: Sensing the Body Through Radio Space

**Authors:** [REMOVED FOR REVIEW]

**Abstract (150 words max):**

We present LIMINAL, an open-source system that renders the invisible electromagnetic topology of a room as a responsive, deformable mesh. The system reveals how the human body distorts radio space through its mere presence. Four low-cost LoRa nodes (~£18 each) are placed at the corners of a space and continuously measure signal strength across all six inter-node paths. When a person moves through the sensing area, their body attenuates radio signals along the paths they cross, producing measurable drops in received signal strength. A real-time browser-based visualiser translates these fluctuations into a living topographic surface. The mesh dips where a body absorbs radio energy and recovers as the person moves on. We describe the system's design, report observations from deployment, and discuss how passive radio sensing reframes the body as an electromagnetic presence: always shaping invisible space, but never before able to see it.

**Keywords:** radio-frequency sensing, LoRa, embodied interaction, electromagnetic space, RF tomography, open-source hardware, spatial visualisation

---

### PAGES 2–3: The invisible landscape (spread)

**Visual concept:** Full-bleed spread. Left page: a photograph of an apparently empty room where the system is deployed. Clean, still, nothing visible happening. Right page: the same room from the same angle, overlaid with a semi-transparent capture of the LIMINAL visualiser mesh composited onto the photograph. The mesh should be clearly deforming where a person (visible as a faint silhouette or motion blur) is crossing a signal path.

**Annotation text (minimal, placed at margins):**

> Every room has an electromagnetic architecture. Radio signals from WiFi routers, Bluetooth devices, and LoRa transmitters fill the space with energy that reflects off walls, passes through doors, and is absorbed by human bodies. This topology is as real as the furniture, but entirely invisible.

> LIMINAL makes it perceptible. Four radio nodes map six signal paths through a space. When a body enters, the topology deforms. What you see here is not a simulation. It is a live capture of radio energy being disrupted by a person walking through a room.

**Images needed:**
- [ ] Photo: empty deployment room, clean composition, wide angle
- [ ] Photo: same angle, person mid-stride between two nodes
- [ ] Screenshot: visualiser mesh showing clear deformation
- [ ] Composite: mesh overlaid on room photograph

---

### PAGES 4–5: Lineage (spread)

**Visual concept:** A visual timeline or triptych positioning LIMINAL within its design research lineage. Three columns or zones:

**Left column: Hertzian Tales (Dunne, 2005)**
A scan or redrawing of one of Dunne's hertzian space diagrams. This was the theoretical proposal that electronic objects inhabit invisible radio fields, and that design should engage with this electromagnetic materiality.

**Centre column: Immaterials (Arnall, Martinussen et al., 2009–2013)**
A still from the WiFi light-painting work: the long-exposure photograph showing a vertical bar of LED lights revealing WiFi signal strength as it is carried through urban space. This work made radio *visible*, but as a static, photographic trace.

**Right column: LIMINAL (2026)**
A capture of the live visualiser responding to a body. The shift is clear: from theoretical proposal, to photographic revelation, to continuous embodied interaction. The body is no longer a camera or probe. It is the signal itself.

**Annotation text:**

> Dunne proposed that electronic objects exist in an invisible "hertzian space" that design largely ignores [1]. Arnall and colleagues developed photographic techniques to reveal the spatial materiality of WiFi and RFID fields, producing evocative images of radio as a fixed condition [2,3]. LIMINAL extends this lineage from image to interaction. The radio landscape is not captured but inhabited, not photographed but felt, sensed continuously through the body's own electromagnetic shadow.

**Images needed:**
- [ ] Hertzian Tales diagram (seek permission or redraw)
- [ ] Immaterials WiFi light-painting still (seek permission from Arnall/YOUrban)
- [ ] LIMINAL visualiser capture with body-in-space

---

### PAGES 6–7: How it works (spread)

**Visual concept:** A technical-but-beautiful annotated diagram spread. This is the system architecture made visual. Not a flowchart, but a spatial composition showing the physical setup and data flow.

**Left page: The physical system**
An annotated photograph or illustrated diagram of the four nodes in situ. Dashed lines drawn between all six node pairs, labelled with example RSSI values. Annotations point to key hardware elements: the SX1262 LoRa radio, the SSD1306 OLED screen showing live readings, the antenna, the USB connection to the laptop.

**Right page: The data journey**
A visual sequence showing how radio becomes mesh:

1. **Radio.** A waveform or signal icon. "Each node pings in a 250ms TDMA slot."
2. **RSSI.** A number: -74 dBm. "Every received ping reports signal strength."
3. **Bridge.** A terminal window capture. "JSON streams over USB to a Python WebSocket bridge."
4. **Mesh.** A small visualiser capture. "Six RSSI values deform a spring-damped topographic surface."

Each step rendered as a visual panel with a one-line annotation beneath.

**Annotation text:**

> The system uses time-division multiple access. Each node transmits in a dedicated 250ms slot, completing a full cycle every second. With four nodes, six unique signal paths are measured continuously. A single USB-connected node captures all readings, as it hears the other three directly. The bridge translates serial JSON into a WebSocket stream consumed by a P5.js visualiser, which maps each signal path to a corridor on a 2D mesh grid. Spring-and-damping physics produce smooth, organic deformation. The mesh dips where signal attenuates and recovers as the disruption passes.

**Images needed:**
- [ ] Annotated photo or diagram of 4-node setup with signal paths
- [ ] Close-up photo of Heltec V3 OLED showing RSSI readings
- [ ] Screenshot of bridge terminal output
- [ ] Annotated visualiser screenshot showing mesh physics

---

### PAGE 8: The body as signal (full page)

**Visual concept:** The key conceptual image. A sequence of 4–6 small visualiser captures arranged vertically, each showing a progressive timestep as a person walks across one signal path. The mesh deforms, reaches maximum dip, then recovers. Annotated with timestamps and RSSI values at the midpoint.

Alternatively: a single, high-quality composite showing the body as a disruption in the radio field.

**Annotation text:**

> The human body is approximately 60% water. Water absorbs radio energy at the frequencies used by LoRa (868 MHz). When a person walks between two nodes, they absorb a measurable fraction of the signal, typically 5 to 15 dB depending on distance, angle, and body mass. This attenuation is the body's radio shadow: proof of electromagnetic presence in a space.

> LIMINAL does not instrument the body. There are no wearables, no cameras, no markers. The person is sensed entirely through their passive effect on ambient radio topology. The body is not a user of the system. It is the phenomenon the system observes.

**Images needed:**
- [ ] Sequence: 4–6 visualiser captures showing person crossing a path over time
- [ ] OR: single high-impact composite of body + mesh deformation
- [ ] Annotated with RSSI values and timestamps

---

### PAGE 9: Observations from deployment (full page)

**Visual concept:** A grid of annotated visualiser captures from different scenarios. 2×3 grid or similar layout.

**Scenarios to capture and annotate:**

| Capture | Observation |
|---|---|
| Empty room, no movement | "Baseline: gentle ambient drift from multipath reflections. The mesh breathes even when nobody is present. Walls, furniture, and atmospheric conditions all shape radio topology." |
| One person walking slowly | "A single body produces a clear, trackable dip along the path it crosses. Recovery time is roughly two seconds." |
| One person standing still in centre | "A stationary body creates a persistent depression. The mesh settles around the obstruction like water around a stone." |
| Two people crossing paths | "Multiple bodies create overlapping attenuation patterns. The mesh becomes more complex, harder to decompose visually but richer in information." |
| Person walking close to a node | "Proximity to a node produces sharp, localised disruption. The strongest effect occurs when the body is directly between two nodes, not near one." |
| Door opening/closing | "Architectural changes register. An opening door shifts signal paths measurably. The building is part of the electromagnetic landscape." |

**Images needed:**
- [ ] 6 visualiser captures, each clearly labelled
- [ ] Each capture taken during a specific, documented scenario

---

### PAGE 10: Openness and accessibility (full page)

**Visual concept:** Screenshots of the GitHub repository, the web flasher interface, and the OLED display. This page argues that the system is designed for accessibility. Artists, designers, and educators can reproduce it without embedded development experience.

**Panel 1:** The GitHub Pages web flasher, showing the four Flash buttons. Annotation: "Browser-based firmware flashing. No development tools required. Chrome and a USB cable."

**Panel 2:** The Heltec V3 board, roughly £18. Annotation: "Total hardware cost for a four-node system: under £80."

**Panel 3:** The visualiser running in a browser. Annotation: "Real-time visualisation in P5.js. Open source. Runs on any laptop."

**Panel 4:** The OLED screen showing live RSSI. Annotation: "Each node displays its own readings. The system is legible at every layer."

**Annotation text:**

> LIMINAL is released as open-source hardware and software under GPL v3. The entire system (firmware, bridge, and visualiser) is contained in a single repository. Pre-compiled firmware can be flashed directly from a browser using ESP Web Tools, eliminating the need for PlatformIO, Arduino IDE, or any embedded development toolchain. The design decision to make the system reproducible without specialist knowledge is deliberate. If electromagnetic space is a civic and creative concern, the tools to perceive it should not be locked behind engineering expertise.

**Images needed:**
- [ ] Screenshot: GitHub Pages flasher interface
- [ ] Photo: Heltec V3 board with antenna, next to a coin for scale
- [ ] Screenshot: visualiser in LIVE mode
- [ ] Photo: OLED close-up showing readings

---

### PAGE 11: Implications and futures (full page)

**Visual concept:** A speculative spread showing potential extensions. Could be rendered as sketches, diagrams, or annotated concept images.

**Sketch 1, Sonification:** A pair of headphones overlaid on the mesh. "Each of the six signal pairs mapped to a Tone.js oscillator. Movement becomes involuntary music."

**Sketch 2, Projection mapping:** A floor-mounted projector throwing the mesh onto the physical space. "The radio topology overlaid on the room it describes."

**Sketch 3, Crowd sensing:** A larger outdoor space with 8 to 12 nodes. "Scaling to 12 nodes produces 66 signal paths, sufficient for crowd-density estimation at public events."

**Sketch 4, Multi-room:** Two adjacent rooms sharing border nodes. "Chaining spaces to track movement flow between rooms."

**Annotation text:**

> The architecture scales. N nodes produce N(N-1)/2 signal paths. With 8 nodes, 28 paths offer sufficient spatial resolution for rough position estimation. With 12, the 66 paths approach true RF tomography: heatmaps of attenuation density that could map crowd flow at festivals, exhibitions, or public spaces. The LoRa radios used here reach 1 to 2 km line of sight. An outdoor deployment at this range would sense bodies across an entire plaza.

> Other modalities extend the perceptual range. Sonification maps radio disruption to sound, creating an audible landscape of presence. Projection mapping closes the loop between the invisible phenomenon and the physical space it occupies. Each extension reframes the same question: what does it mean to be electromagnetically present?

---

### PAGE 12: References

[1] Dunne, A. (2005). *Hertzian Tales: Electronic Products, Aesthetic Experience, and Critical Design.* MIT Press.

[2] Arnall, T. and Martinussen, E.S. (2010). Depth of Field: Discursive design research through film. *FORMakademisk*, 3(1).

[3] Martinussen, E.S., Knutsen, J., and Arnall, T. (2014). Satellite Lamps. *Kairos: A Journal of Rhetoric, Technology, and Pedagogy*, 19(1).

[4] Wilson, J. and Patwari, N. (2010). Radio Tomographic Imaging with Wireless Networks. *IEEE Transactions on Mobile Computing*, 9(5), 621–632.

[5] Patwari, N. and Wilson, J. (2011). Spatial Models for Human Motion-Induced Signal Strength Variance on Static Links. *IEEE Transactions on Information Forensics and Security*, 6(3), 791–802.

[6] Greenfield, A. (2013). *Against the Smart City.* Do Projects.

[7] Haque, U. (2004). *Sky Ear.* [Installation]. http://haque.co.uk/skyear.php

[8] Bridle, J. (2012). *Drone Shadows.* [Installation/intervention].

[9] Weiser, M. (1991). The Computer for the 21st Century. *Scientific American*, 265(3), 94–104.

[10] Ishii, H. and Ullmer, B. (1997). Tangible Bits: Towards Seamless Interfaces between People, Bits and Atoms. *Proceedings of CHI '97*, 234–241.

---

## Production checklist

### Photo/capture shoot list
- [ ] Empty deployment room: wide angle, clean, well-lit
- [ ] Same angle with person mid-stride between nodes
- [ ] Four-node setup showing all hardware in situ
- [ ] Close-up: Heltec V3 OLED showing RSSI readings
- [ ] Close-up: Heltec V3 board with antenna (coin for scale)
- [ ] Bridge terminal output screenshot
- [ ] Visualiser screenshot: LIVE mode, baseline (no movement)
- [ ] Visualiser screenshot: single person crossing a path
- [ ] Visualiser screenshot: person standing still in centre
- [ ] Visualiser screenshot: two people crossing
- [ ] Visualiser screenshot: near-node disruption
- [ ] Visualiser screenshot: door opening
- [ ] Visualiser timestep sequence (4–6 frames, one crossing event)
- [ ] GitHub Pages flasher interface screenshot
- [ ] Composite: mesh overlaid on room photograph

### Image permissions needed
- [ ] Hertzian Tales diagram: contact MIT Press or redraw
- [ ] Immaterials WiFi light-painting: contact Timo Arnall / YOUrban

### Format reminders
- Max 12 pages excluding references
- Use InDesign template from TEI (or Word/PowerPoint)
- Double-blind: remove all author names and affiliations
- Abstract ≤ 150 words on page 1
- Images are PRIMARY, text is scaffolding
- Every image must play a meaningful role, no decoration
- Aim for roughly 70% visual, 30% text per spread
- Submit by **July 31st AoE**

### Review criteria (design pages to address these)
- Does the work require a Pictorial format? Yes: radio-to-mesh is inherently visual
- Is the contribution original and complete? Novel commodity LoRa for embodied spatial sensing
- Are images emphasised over text? 70/30 visual/text ratio
- Are implications for TEI community clear? Passive body sensing, open-source, civic legibility
- Does every image play a meaningful role? No decorative images
- Does placement compose a good narrative? Invisible, then visible, then how, then what it means