// ═══════════════════════════════════════════════════════════
// LIMINAL — Heltec V3 LoRa Radio-Space Sensing Firmware
// ═══════════════════════════════════════════════════════════
// Hardware: Heltec WiFi LoRa 32 V3 (ESP32-S3 + SX1262)
// NODE_ID set via platformio.ini environments (0-3)
// Build all:   pio run
// Flash node 0: pio run -e node0 -t upload
// ═══════════════════════════════════════════════════════════

#include <Arduino.h>
#include <SPI.h>
#include <RadioLib.h>
#include <Wire.h>
#include <SSD1306Wire.h>

// ── CONFIG (set via build flags) ──────────────────────────
#ifndef NODE_ID
#define NODE_ID 0
#endif
#ifndef FREQUENCY
#define FREQUENCY 868.0    // MHz — 915.0 for US/AU
#endif

#define NUM_NODES      4
#define BANDWIDTH      125.0   // kHz
#define SPREAD_FACTOR  7
#define CODING_RATE    5       // 4/5
#define TX_POWER       14      // dBm
#define SYNC_WORD      0x42
#define PREAMBLE_LEN   8
#define SLOT_MS        250     // TDMA slot per node (SX1262 needs a bit more)
#define CYCLE_MS       (SLOT_MS * NUM_NODES)
#define PING_MAGIC     0xCA

// ── Heltec V3 Pin Definitions ─────────────────────────────
// LoRa SX1262
#define LORA_SCK    9
#define LORA_MISO   11
#define LORA_MOSI   10
#define LORA_CS     8
#define LORA_RST    12
#define LORA_BUSY   13
#define LORA_DIO1   14

// OLED SSD1306
#define OLED_SDA    17
#define OLED_SCL    18
#define OLED_RST    21

// Vext power control (powers OLED and other external devices)
#define VEXT_PIN    36

// ── OBJECTS ───────────────────────────────────────────────
SPIClass loraSPI(FSPI);
SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY, loraSPI);
SSD1306Wire oled(0x3c, OLED_SDA, OLED_SCL);

// ── STATE ─────────────────────────────────────────────────
struct PeerData {
  float rssi;
  float snr;
  unsigned long lastSeen;
  bool active;
};

PeerData peers[NUM_NODES];
unsigned long cycleStart = 0;
unsigned long lastDisplay = 0;
uint16_t seqNum = 0;
volatile bool rxFlag = false;
volatile bool txDone = false;

// ── PACKET ────────────────────────────────────────────────
struct __attribute__((packed)) Packet {
  uint8_t  magic;
  uint8_t  from;
  uint16_t seq;
  char     tag[4];  // "PING"
};

// ── ISR CALLBACKS ─────────────────────────────────────────
void onReceive(void) { rxFlag = true; }
void onTransmitDone(void) { txDone = true; }

// ── SETUP ─────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(1000);  // Give USB CDC time to init on ESP32-S3

  // Enable Vext (powers OLED)
  pinMode(VEXT_PIN, OUTPUT);
  digitalWrite(VEXT_PIN, LOW);  // LOW = ON for V3
  delay(50);

  // Reset OLED
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);
  delay(50);

  // Init OLED
  oled.init();
  oled.setFont(ArialMT_Plain_10);
  oled.clear();
  oled.drawString(0, 0, "LIMINAL [" + String(NODE_ID) + "]");
  oled.drawString(0, 14, "Init SX1262...");
  oled.display();

  // Init LoRa SPI
  loraSPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);

  // Init SX1262
  Serial.print("LIMINAL:INIT:SX1262...");
  int state = radio.begin(FREQUENCY, BANDWIDTH, SPREAD_FACTOR, CODING_RATE, SYNC_WORD, TX_POWER, PREAMBLE_LEN);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.println("FAILED:" + String(state));
    oled.drawString(0, 28, "LoRa FAILED! err:" + String(state));
    oled.display();
    while (1) delay(1000);
  }
  Serial.println("OK");

  // Configure SX1262
  radio.setCRC(true);
  radio.setDio1Action(onReceive);

  // Init peers
  for (int i = 0; i < NUM_NODES; i++) {
    peers[i] = { -120.0f, -20.0f, 0, false };
  }

  // Stagger start for loose TDMA sync
  delay(NODE_ID * SLOT_MS);
  cycleStart = millis();

  // Start listening
  radio.startReceive();

  Serial.println("LIMINAL:BOOT:" + String(NODE_ID));

  oled.clear();
  oled.drawString(0, 0, "LIMINAL [" + String(NODE_ID) + "] READY");
  oled.drawString(0, 14, String(FREQUENCY, 0) + " MHz  SF" + String(SPREAD_FACTOR));
  oled.display();
}

// ── TRANSMIT ──────────────────────────────────────────────
void sendPing() {
  Packet pkt;
  pkt.magic = PING_MAGIC;
  pkt.from  = NODE_ID;
  pkt.seq   = seqNum++;
  memcpy(pkt.tag, "PING", 4);

  // Transmit (blocking for small packet)
  radio.standby();
  txDone = false;
  int state = radio.transmit((uint8_t*)&pkt, sizeof(pkt));

  // Back to receive mode immediately
  rxFlag = false;
  radio.startReceive();
}

// ── RECEIVE ───────────────────────────────────────────────
void checkReceive() {
  if (!rxFlag) return;
  rxFlag = false;

  Packet pkt;
  int state = radio.readData((uint8_t*)&pkt, sizeof(pkt));

  // Restart listening
  radio.startReceive();

  if (state != RADIOLIB_ERR_NONE) return;
  if (pkt.magic != PING_MAGIC) return;
  if (pkt.from >= NUM_NODES || pkt.from == NODE_ID) return;

  float rssi = radio.getRSSI();
  float snr  = radio.getSNR();

  peers[pkt.from].rssi     = rssi;
  peers[pkt.from].snr      = snr;
  peers[pkt.from].lastSeen = millis();
  peers[pkt.from].active   = true;

  // JSON output for bridge.py
  Serial.print("LIMINAL:DATA:{");
  Serial.print("\"node\":" + String(NODE_ID));
  Serial.print(",\"peer\":" + String(pkt.from));
  Serial.print(",\"rssi\":" + String(rssi, 1));
  Serial.print(",\"snr\":" + String(snr, 1));
  Serial.print(",\"seq\":" + String(pkt.seq));
  Serial.print(",\"t\":" + String(millis()));
  Serial.println("}");
}

// ── OLED DISPLAY ──────────────────────────────────────────
void updateDisplay() {
  if (millis() - lastDisplay < 500) return;
  lastDisplay = millis();

  oled.clear();
  oled.setFont(ArialMT_Plain_10);
  oled.drawString(0, 0, "LIMINAL [" + String(NODE_ID) + "]");

  int row = 0;
  for (int i = 0; i < NUM_NODES; i++) {
    if (i == NODE_ID) continue;
    int y = 16 + row * 16;
    row++;

    if (!peers[i].active || millis() - peers[i].lastSeen > 5000) {
      oled.drawString(0, y, "Node " + String(i) + ": --");
    } else {
      String line = "Node " + String(i) + ": "
        + String(peers[i].rssi, 0) + "dBm "
        + String(peers[i].snr, 1) + "dB";
      oled.drawString(0, y, line);

      // Signal bar
      int barW = map(constrain((int)peers[i].rssi, -120, -30), -120, -30, 2, 40);
      oled.fillRect(90, y + 2, barW, 8);
    }
  }
  oled.display();
}

// ── MAIN LOOP ─────────────────────────────────────────────
void loop() {
  unsigned long now = millis();
  unsigned long elapsed = (now - cycleStart) % CYCLE_MS;
  unsigned long mySlotStart = NODE_ID * SLOT_MS;

  // Transmit in our TDMA slot
  if (elapsed >= mySlotStart && elapsed < mySlotStart + 15) {
    sendPing();
  }

  // Check for received packets
  checkReceive();

  // Mark stale peers
  for (int i = 0; i < NUM_NODES; i++) {
    if (peers[i].active && now - peers[i].lastSeen > 10000) {
      peers[i].active = false;
    }
  }

  updateDisplay();
  delay(1);
}