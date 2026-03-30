# LIMINAL: Making Radio Space Tangible Through LoRa Tomography

## Abstract

We present LIMINAL, an open-source system that makes the invisible electromagnetic architecture of physical space perceptible in real time. Four low-cost LoRa radio nodes (Heltec V3, ~£18 each) are positioned at the corners of a space and continuously ping each other in a time-division cycle. By monitoring received signal strength (RSSI) and signal-to-noise ratio (SNR) across all six node-to-node paths, the system constructs a live topographic mesh of radio energy flowing through the environment. When a person walks through the sensing area, their body (composed largely of water) absorbs and scatters radio energy, producing measurable attenuation along the signal paths they cross. The accompanying browser-based visualiser renders these fluctuations as a deformable surface. The mesh dips where the body disrupts a signal corridor and recovers as the person moves on. The result is a real-time, continuous representation of the body's radio shadow: an invisible phenomenon made legible through spatial sensing and visual translation.

LIMINAL builds on a lineage of design research concerned with the legibility of electromagnetic phenomena. Dunne's *Hertzian Tales* (2005) argued that electronic objects inhabit an invisible radio landscape that design largely ignores. Arnall, Martinussen and colleagues' *Immaterials* project (2009–2013) developed photographic and cinematic techniques, including light-painting of RFID fields and WiFi networks, to reveal the spatial materiality of wireless systems in static and time-lapse form. Where Immaterials produced evocative images and films of radio as a fixed condition of urban space, LIMINAL shifts to continuous, embodied, real-time interaction. The human body is not a camera or probe but the active agent whose presence *is* the signal, sensed and rendered as it moves.

The system's contribution is threefold. First, it demonstrates that meaningful radio-frequency tomography can be achieved with commodity hardware and open-source software, lowering the barrier from laboratory RF imaging systems to a setup reproducible by artists, designers, and educators. The entire system (firmware, serial-to-WebSocket bridge, and P5.js visualiser) is available as a single GitHub repository with browser-based firmware flashing, requiring no embedded development experience to deploy. Second, it foregrounds the body as the primary interactant with electromagnetic space, aligning with TEI's concern for embodied, spatial interaction. The body is not instrumented with sensors or markers. It is sensed passively, through its effect on the radio environment it inhabits. Third, by rendering radio topology as a responsive physical surface rather than a data dashboard, the system invites a kinaesthetic, exploratory mode of engagement. Users discover their radio shadow through movement, gesture, and spatial play.

We describe the technical implementation (SX1262 LoRa TDMA firmware, Python WebSocket bridge, P5.js mesh physics), report initial observations from deployment in a 10m × 8m indoor space, and discuss design implications for spatial sensing systems that use the body's electromagnetic presence as input. We position the work within the broader context of making infrastructure legible, arguing that as wireless systems increasingly mediate everyday experience, the capacity to perceive and engage with radio space becomes a matter of both creative practice and civic literacy.

## Keywords

Radio-frequency sensing; LoRa; electromagnetic space; embodied interaction; hertzian space; RF tomography; open-source hardware; spatial visualisation

## Submission track

Papers / Pictorials: TEI '27, The Body in Space

## Relevance to TEI '27 theme

LIMINAL directly addresses the conference theme "The Body in Space" by treating the human body as an electromagnetic phenomenon: a material presence that reshapes the radio topology of any space it occupies. The system makes this shaping visible and interactive, inviting participants to explore their own spatial agency in a medium they cannot otherwise perceive.