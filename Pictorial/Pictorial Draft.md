# LIMINAL: Sensing the Body Through Radio Space

## TEI '27 Pictorial Submission — Formatted to InDesign Template Spec

**Format:** US Letter, landscape, max 12 pages excl. references
**Margins:** Top 2.54cm, Bottom 2.1cm, Left/Right 1.3cm
**Title:** Arial 18pt bold
**Authors:** Times New Roman 12pt (bold names, regular affiliations)
**Body text:** Times New Roman 10pt
**References:** ACM format, numbered square brackets, TNR 10pt

---

### PAGE 1: Title and abstract

**Title (Arial 18pt bold):**
LIMINAL: Sensing the Body Through Radio Space

**Authors (TNR 12pt, leave blank for review):**
[REMOVED FOR DOUBLE-BLIND REVIEW]

**Abstract (TNR 10pt, ~150 words):**

We present LIMINAL, an open-source system that renders the invisible electromagnetic topology of a room as a responsive, deformable mesh. The system reveals how the human body distorts radio space through its mere presence. Four low-cost LoRa nodes (~£18 each) are placed at the corners of a space and continuously measure signal strength across all six inter-node paths. When a person moves through the sensing area, their body attenuates radio signals along the paths they cross, producing measurable drops in received signal strength. A real-time browser-based visualiser translates these fluctuations into a living topographic surface. The mesh dips where a body absorbs radio energy and recovers as the person moves on. We describe the system's design, report observations from deployment, and discuss how passive radio sensing reframes the body as an electromagnetic presence: always shaping invisible space, but never before able to see it.

**Authors' Keywords (TNR 10pt):**
radio-frequency sensing; LoRa; embodied interaction; electromagnetic space; RF tomography; open-source hardware; spatial visualisation

**CCS Concepts (TNR 10pt):**
- Human-centred computing~Ubiquitous and mobile computing design and evaluation (High)
- Human-centred computing~Interaction design process and methods (Medium)
- Human-centred computing~Visualization techniques (Medium)
- Hardware~Sensor devices and platforms (Low)

*Generate formatted code at: https://dl.acm.org/ccs/ccs_flat.cfm*

**Layout notes for page 1:**
The right half of this landscape page can hold a single striking image: the visualiser mesh with a visible body-shaped attenuation. This establishes the visual tone immediately.

---

### PAGES 2–3: The invisible landscape (spread)

**Visual composition (primary, ~70% of spread):**
Full-bleed across both pages. Left page: photograph of the empty deployment room. Right page: same angle, overlaid with a semi-transparent capture of the LIMINAL visualiser mesh composited onto the photograph. The mesh deforms where a person (visible as a faint silhouette or motion blur) is crossing a signal path. Visual content can break out of the margins per template guidelines.

**Annotation text (TNR 10pt, placed in margins or over quiet areas of image):**

> Every room has an electromagnetic architecture. Radio signals from WiFi routers, Bluetooth devices, and LoRa transmitters fill the space with energy that reflects off walls, passes through doors, and is absorbed by human bodies. This topology is as real as the furniture, but entirely invisible.

> LIMINAL makes it perceptible. Four radio nodes map six signal paths through a space. When a body enters, the topology deforms. What you see here is not a simulation. It is a live capture of radio energy being disrupted by a person walking through a room.

**Images needed:**
- [ ] Photo: empty deployment room, clean composition, wide angle (300 dpi)
- [ ] Photo: same angle, person mid-stride between two nodes (300 dpi)
- [ ] Screenshot: visualiser mesh showing clear deformation
- [ ] Composite: mesh overlaid on room photograph (prepared in Photoshop at print resolution)

**Alt text:**
"Left: an empty room with four small radio nodes visible at the corners. Right: the same room with a semi-transparent mesh overlay showing a visible dip where a person is walking between two nodes."

---

### PAGES 4–5: Lineage and related work (spread)

**Visual composition (primary):**
A triptych across the top half of the spread, with related work positioning text beneath.

**Column 1: Hertzian Tales (Dunne, 2005) [3]**
Image: A redrawing or permitted reproduction of one of Dunne's hertzian space diagrams.
Annotation (TNR 10pt): "Dunne proposed that electronic objects exist in an invisible 'hertzian space' that design largely ignores [3]. The theoretical groundwork for engaging with electromagnetic materiality."

**Column 2: Immaterials (Arnall, Martinussen et al., 2009–2013) [1, 8]**
Image: A still from the WiFi light-painting work.
Annotation (TNR 10pt): "Arnall and colleagues developed photographic techniques to reveal the spatial materiality of WiFi and RFID fields [1, 8]. Radio made visible, but as a static, photographic trace."

**Column 3: LIMINAL (2026)**
Image: A capture of the live visualiser responding to a body in real time.
Annotation (TNR 10pt): "LIMINAL extends this lineage from image to interaction. The radio landscape is not captured but inhabited, not photographed but felt, sensed continuously through the body's own electromagnetic shadow."

**Related work text (TNR 10pt, lower half of spread):**

> A growing body of research uses radio signals to sense the human body. WiFi Channel State Information (CSI) has been used for binary motion detection through multipath interference analysis [2], and more recently for fine-grained body segmentation and pose estimation using deep learning [4, 14]. MIT's EQ-Radio demonstrated that FMCW radar reflections can extract heartbeat waveforms accurate enough to classify emotional states [15]. These systems treat the body as a target: the goal is to extract information about the person (their presence, pose, or emotional state) from radio signals.

> LIMINAL inverts this relationship. The body is not the subject of classification. It is the agent that reveals the radio environment. The system does not ask "who is there?" or "what are they doing?" It asks "what does the electromagnetic space look like, and how does a body reshape it?" This distinction matters because it shifts the design intent from surveillance and extraction to perception and legibility. The output is not a label or a skeleton. It is a continuously responsive landscape that makes the body's electromagnetic presence visible to the person themselves, in real time, as they move.

**Images needed:**
- [ ] Hertzian Tales diagram (seek permission from MIT Press, or redraw)
- [ ] Immaterials WiFi light-painting still (seek permission from Timo Arnall / YOUrban)
- [ ] LIMINAL visualiser capture with body-in-space

**Alt text:**
"Three images in sequence. Left: a diagram from Dunne's Hertzian Tales showing invisible radio fields around electronic objects. Centre: a long-exposure photograph from the Immaterials project showing WiFi signal strength as a vertical bar of light in an urban street. Right: a screenshot of the LIMINAL visualiser showing a deformable mesh responding to a person's presence in a room."

---

### PAGES 6–7: How it works and why LoRa (spread)

**Visual composition (primary):**
Left page: an annotated photograph or illustrated diagram of the four nodes in situ. Dashed lines drawn between all six node pairs, labelled with example RSSI values (e.g. -49 dBm, -74 dBm). Annotations point to key hardware elements: the SX1262 LoRa radio, the SSD1306 OLED screen, the antenna, the USB connection.

Right page: a four-panel visual sequence showing the data journey from radio to mesh.

**Panel 1: Radio**
Small waveform icon.
"Each node pings in a 250ms TDMA slot. A full cycle completes every second."

**Panel 2: RSSI**
A number displayed large: -74 dBm.
"Every received ping reports signal strength and signal-to-noise ratio."

**Panel 3: Bridge**
A terminal window capture showing JSON output.
"Data streams over USB serial to a Python WebSocket bridge."

**Panel 4: Mesh**
A small visualiser capture.
"Six RSSI values deform a spring-damped topographic surface in P5.js."

**Supporting text (TNR 10pt):**

> The system uses time-division multiple access. Each node transmits in a dedicated 250ms slot, completing a full cycle every second. With four nodes, six unique signal paths are measured continuously. A single USB-connected node captures all readings, as it hears the other three directly. The bridge translates serial JSON into a WebSocket stream consumed by a P5.js visualiser, which maps each signal path to a corridor on a 2D mesh grid. Spring-and-damping physics produce smooth, organic deformation. The mesh dips where signal attenuates and recovers as the disruption passes.

**Technology choice text (TNR 10pt):**

> The choice of LoRa (868 MHz) over higher-frequency alternatives follows from the project's design intent. WiFi-based approaches offer finer spatial resolution and access to CSI phase data, which enables the pose estimation [4, 14] and emotion recognition [15] described above. However, they require network infrastructure, are confined to indoor ranges of 30 to 50 metres, and demand signal processing or machine learning expertise that limits accessibility. LoRa's key properties for LIMINAL's purposes are its long range (1 to 2 km line of sight), minimal infrastructure (self-contained, battery-powered nodes), and low cost (~£18 per node). At 868 MHz, a single human body produces 5 to 15 dB of measurable attenuation across a signal path, which is sufficient for real-time visualisation of presence and movement. The design prioritises legibility and reproducibility over spatial precision. The goal is not to locate the body to the nearest centimetre but to make its electromagnetic presence perceptible at all.

**Also include on this spread:** The inline SVG system architecture diagram (already built into the GitHub Pages Pictorial page). Export at 300 dpi for print.

**Images needed:**
- [ ] Annotated photo of 4-node setup with signal paths drawn on
- [ ] Close-up photo of Heltec V3 OLED showing RSSI readings
- [ ] Screenshot of bridge terminal output
- [ ] Visualiser screenshot showing mesh deformation

**Alt text:**
"Left: four radio nodes placed at the corners of a room with dashed lines showing six signal paths between them, each labelled with a signal strength value. Right: four panels showing the data journey from radio ping to RSSI measurement to serial bridge to browser-based mesh visualisation."

---

### PAGE 8: The body as signal (full page)

**Visual composition (primary):**
A horizontal sequence of 4 to 6 visualiser captures, evenly spaced across the landscape page. Each capture shows a progressive timestep as a person walks across one signal path. The mesh deforms, reaches maximum dip (shown as a white flare against the dark mesh), then recovers. Each frame annotated with a timestamp and the RSSI value at the midpoint of the crossed path.

Example annotation beneath each frame:
t=0s / -48 dBm → t=2s / -61 dBm → t=4s / -58 dBm → t=6s / -49 dBm

**Supporting text (TNR 10pt):**

> The human body is approximately 60% water. Water absorbs radio energy at the frequencies used by LoRa (868 MHz). When a person walks between two nodes, they absorb a measurable fraction of the signal, typically 5 to 15 dB depending on distance, angle, and body mass. This attenuation is the body's radio shadow: proof of electromagnetic presence in a space.

> LIMINAL does not instrument the body. There are no wearables, no cameras, no markers. The person is sensed entirely through their passive effect on ambient radio topology. The body is not a user of the system. It is the phenomenon the system observes. Where related approaches use radio to extract data about the body (its pose [4, 14], its heartbeat [15], its presence as a binary alarm [2]), LIMINAL uses the body to reveal data about the radio space. The person is not surveilled. They are given sight.

**Images needed:**
- [ ] Sequence: 4 to 6 visualiser captures at timed intervals during one crossing event
- [ ] Each annotated with timestamp and RSSI value

**Alt text:**
"A horizontal sequence of six visualiser screenshots showing a mesh that is initially calm, then dips sharply as a person crosses a signal path, then recovers to its baseline state. RSSI values beneath each frame show the signal dropping from minus 48 to minus 61 dBm and returning."

---

### PAGE 9: Observations from deployment (full page)

**Visual composition (primary):**
A 2×3 grid of annotated visualiser captures, each from a specific documented scenario. Each cell contains a screenshot and a one-sentence observation in TNR 10pt beneath it.

| Capture | Annotation |
|---|---|
| Empty room, no movement | "Baseline: gentle ambient drift from multipath reflections. The mesh breathes even when nobody is present." |
| One person walking slowly | "A single body produces a clear, trackable dip along the path it crosses. Recovery time is roughly two seconds." |
| One person standing still in centre | "A stationary body creates a persistent depression. The mesh settles around the obstruction like water around a stone." |
| Two people crossing paths | "Multiple bodies create overlapping attenuation patterns. The mesh becomes more complex but richer in information." |
| Person walking close to a node | "The strongest effect occurs when the body is directly between two nodes, not near one." |
| Door opening/closing | "An opening door shifts signal paths measurably. The building is part of the electromagnetic landscape." |

**Images needed:**
- [ ] 6 visualiser captures, each from a specific documented scenario (300 dpi screenshots)

**Alt text:**
"A grid of six screenshots from the visualiser. Each shows a different scenario: empty room with a calm mesh, one person causing a dip, a stationary person causing a persistent depression, two people creating overlapping patterns, near-node disruption, and a door opening causing a shift in the mesh baseline."

---

### PAGE 10: Openness and accessibility (full page)

**Visual composition (primary):**
Four panels arranged across the landscape page, each containing a photograph or screenshot with a one-line annotation.

**Panel 1:** Screenshot of the GitHub Pages web flasher showing four Flash buttons.
"Browser-based firmware flashing. No development tools required. Chrome and a USB cable."

**Panel 2:** Photograph of the Heltec V3 board with antenna, next to a coin for scale.
"Total hardware cost for a four-node system: under £80."

**Panel 3:** Screenshot of the visualiser in LIVE mode with the HUD showing all six signal pairs.
"Real-time visualisation in P5.js. Open source. Auto-calibrates to the signal environment."

**Panel 4:** Close-up photograph of the OLED screen showing live RSSI readings.
"Each node displays its own readings. The system is legible at every layer."

**Supporting text (TNR 10pt):**

> LIMINAL is released as open-source hardware and software under GPL v3 [7]. The entire system (firmware, bridge, and visualiser) is contained in a single repository. Pre-compiled firmware can be flashed directly from a browser using ESP Web Tools, eliminating the need for PlatformIO, Arduino IDE, or any embedded development toolchain. The design decision to make the system reproducible without specialist knowledge is deliberate. If electromagnetic space is a civic and creative concern, the tools to perceive it should not be locked behind engineering expertise. This accessibility distinguishes LIMINAL from related RF sensing systems [2, 4, 14, 15], which require custom hardware configurations, machine learning pipelines, or signal processing expertise that confines them to laboratory settings.

**Images needed:**
- [ ] Screenshot: GitHub Pages flasher interface
- [ ] Photo: Heltec V3 board with antenna, coin for scale (300 dpi)
- [ ] Screenshot: visualiser in LIVE mode
- [ ] Photo: OLED close-up showing readings (300 dpi)

**Alt text:**
"Four panels. Top left: a browser interface with four blue buttons labelled Flash Node 0 through Flash Node 3. Top right: a small circuit board with a wire antenna next to a one pound coin for scale. Bottom left: a dark browser window showing a glowing mesh with signal readings in the top right corner. Bottom right: a close-up of a small OLED screen displaying three rows of signal strength data."

---

### PAGE 11: Implications and futures (full page)

**Visual composition (primary):**
Four speculative sketches or concept diagrams arranged across the page. These can be hand-drawn or clean vector illustrations. Each accompanied by a short caption.

**Sketch 1: Sonification**
"Each of the six signal pairs mapped to an oscillator. Signal attenuation becomes pitch shift. Movement becomes involuntary music."

**Sketch 2: Projection mapping**
"A floor-mounted projector overlays the mesh onto the physical space. The radio topology becomes spatially co-located with the room it describes."

**Sketch 3: Crowd sensing**
"Scaling to 12 nodes produces 66 signal paths, sufficient for crowd-density estimation at public events."

**Sketch 4: Multi-room**
"Chaining spaces by sharing border nodes. Movement flow tracked between adjacent rooms."

**Supporting text (TNR 10pt):**

> The architecture scales. N nodes produce N(N-1)/2 signal paths. With 8 nodes, 28 paths offer sufficient spatial resolution for rough position estimation. With 12, the 66 paths approach true RF tomography [11, 12]: heatmaps of attenuation density that could map crowd flow at festivals, exhibitions, or public spaces. The LoRa radios used here reach 1 to 2 km line of sight. An outdoor deployment at this range would sense bodies across an entire plaza.

> Other modalities extend the perceptual range. Sonification maps radio disruption to sound, creating an audible landscape of presence. Projection mapping closes the loop between the invisible phenomenon and the physical space it occupies. Each extension reframes the same question: what does it mean to be electromagnetically present?

> Importantly, LIMINAL's approach to sensing raises different ethical questions than the surveillance-oriented RF systems it is related to [4, 14, 15]. The system cannot identify individuals, estimate poses, or infer emotional states. It perceives presence and movement at the resolution of a signal path, not a skeleton or a heartbeat. This coarseness is a feature, not a limitation. It positions the system as a perceptual tool rather than a monitoring one.

---

### PAGE 12: References

See separate references.md file.

---

## Production checklist

### Before composing in InDesign
- [ ] Download TEI Pictorials InDesign template
- [ ] Set page size: US Letter, landscape
- [ ] Verify margins: Top 2.54cm, Bottom 2.1cm, Left/Right 1.3cm
- [ ] Set body text: Times New Roman 10pt
- [ ] Set title: Arial 18pt bold
- [ ] Leave author/affiliation fields blank (double-blind)
- [ ] Leave header/footer clear (Sheridan adds these for camera-ready)
- [ ] Generate ACM CCS concepts at https://dl.acm.org/ccs/ccs_flat.cfm

### Photo/capture shoot list (all images at 300 dpi for print)
- [ ] Empty deployment room: wide angle, clean, well-lit
- [ ] Same angle with person mid-stride between nodes
- [ ] Four-node setup showing all hardware in situ
- [ ] Close-up: Heltec V3 OLED showing RSSI readings
- [ ] Close-up: Heltec V3 board with antenna (coin for scale)
- [ ] Bridge terminal output screenshot
- [ ] Visualiser: LIVE mode, baseline (no movement)
- [ ] Visualiser: single person crossing a path
- [ ] Visualiser: person standing still in centre
- [ ] Visualiser: two people crossing
- [ ] Visualiser: near-node disruption
- [ ] Visualiser: door opening
- [ ] Visualiser timestep sequence (4 to 6 frames)
- [ ] GitHub Pages flasher interface screenshot
- [ ] Composite: mesh overlaid on room photograph

### Image permissions needed
- [ ] Hertzian Tales diagram: contact MIT Press or redraw
- [ ] Immaterials WiFi light-painting: contact Timo Arnall / YOUrban

### Accessibility (per template guidelines)
- [ ] Add alt text to all figures in InDesign (Object > Object Export Options > Alt Text)
- [ ] Mark table headings
- [ ] Generate tagged PDF
- [ ] Verify default language is set to English
- [ ] Set tab order to "Use Document Structure"
- [ ] Check with Adobe "Read Out Loud" function

### ACM compliance
- [ ] PDF must be ACM DL Compliant
- [ ] Copyright block on page 1 (updated during rights-review process if accepted)
- [ ] All images resized to 300 dpi before placing
- [ ] File size: aim well under 150 MB
- [ ] References in ACM format with square brackets

### Submission
- [ ] Submit abstract and author info by **July 31st AoE**
- [ ] Submit full Pictorial PDF by **~August 7th AoE** (check TEI '27 dates when published)
- [ ] Submit via Precision Conference (PCS) system
- [ ] Ensure no author names or affiliations appear anywhere in the PDF
- [ ] Do not include page numbers in header/footer

### Language and style
- [ ] Consistent British English spelling throughout
- [ ] Use £ GBP for all currency references
- [ ] Define all technical terms on first use (e.g. "Received Signal Strength Indicator (RSSI)")
- [ ] Explain all acronyms on first use (e.g. "time-division multiple access (TDMA)")
- [ ] Avoid colloquial language
- [ ] Use gender-neutral language
- [ ] Use unambiguous date formats