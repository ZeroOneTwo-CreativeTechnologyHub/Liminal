// LIMINAL — Heltec V2 LoRa Radio-Space Sensing Firmware
// NODE_ID set via platformio.ini build flags (0-3)

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "HT_SSD1306Wire.h"

#ifndef NODE_ID
#define NODE_ID 0
#endif
#ifndef FREQUENCY
#define FREQUENCY 868E6
#endif

#define NUM_NODES      4
#define BANDWIDTH      125E3
#define SPREAD_FACTOR  7
#define TX_POWER       14
#define SYNC_WORD      0x42
#define SLOT_MS        200
#define CYCLE_MS       (SLOT_MS * NUM_NODES)
#define GUARD_MS       20
#define PING_MAGIC     0xCA

#define LORA_SCK   5
#define LORA_MISO  19
#define LORA_MOSI  27
#define LORA_CS    18
#define LORA_RST   14
#define LORA_IRQ   26

SSD1306Wire oled(0x3c, SDA_OLED, SCL_OLED, RST_OLED, GEOMETRY_128_64);

struct PeerData { float rssi; float snr; unsigned long lastSeen; bool active; };
PeerData peers[NUM_NODES];
unsigned long cycleStart = 0;
unsigned long lastDisplay = 0;
uint16_t seqNum = 0;

struct __attribute__((packed)) Packet {
  uint8_t magic; uint8_t from; uint16_t seq; char tag[4];
};

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000);

  oled.init(); oled.setFont(ArialMT_Plain_10); oled.clear();
  oled.drawString(0, 0, "LIMINAL [" + String(NODE_ID) + "]");
  oled.drawString(0, 14, "Initializing LoRa..."); oled.display();

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

  if (!LoRa.begin(FREQUENCY)) {
    Serial.println("ERROR:LORA_INIT_FAILED");
    oled.drawString(0, 28, "LoRa FAILED!"); oled.display();
    while (1) delay(1000);
  }

  LoRa.setSpreadingFactor(SPREAD_FACTOR);
  LoRa.setSignalBandwidth(BANDWIDTH);
  LoRa.setTxPower(TX_POWER);
  LoRa.setSyncWord(SYNC_WORD);
  LoRa.enableCrc();

  for (int i = 0; i < NUM_NODES; i++)
    peers[i] = { -120.0f, -20.0f, 0, false };

  delay(NODE_ID * SLOT_MS);
  cycleStart = millis();

  Serial.println("LIMINAL:BOOT:" + String(NODE_ID));
  oled.clear();
  oled.drawString(0, 0, "LIMINAL [" + String(NODE_ID) + "] READY");
  oled.drawString(0, 14, String(FREQUENCY / 1E6, 0) + " MHz  SF" + String(SPREAD_FACTOR));
  oled.display();
}

void sendPing() {
  Packet pkt; pkt.magic = PING_MAGIC; pkt.from = NODE_ID;
  pkt.seq = seqNum++; memcpy(pkt.tag, "PING", 4);
  LoRa.beginPacket(); LoRa.write((uint8_t*)&pkt, sizeof(pkt)); LoRa.endPacket();
}

void checkReceive() {
  int pktSize = LoRa.parsePacket();
  if (pktSize < (int)sizeof(Packet)) return;
  Packet pkt; uint8_t* ptr = (uint8_t*)&pkt;
  for (int i = 0; i < (int)sizeof(Packet); i++) {
    if (LoRa.available()) ptr[i] = LoRa.read(); else return;
  }
  if (pkt.magic != PING_MAGIC) return;
  if (pkt.from >= NUM_NODES || pkt.from == NODE_ID) return;

  float rssi = LoRa.packetRssi();
  float snr  = LoRa.packetSnr();
  peers[pkt.from].rssi = rssi;
  peers[pkt.from].snr = snr;
  peers[pkt.from].lastSeen = millis();
  peers[pkt.from].active = true;

  Serial.print("LIMINAL:DATA:{");
  Serial.print("\"node\":" + String(NODE_ID));
  Serial.print(",\"peer\":" + String(pkt.from));
  Serial.print(",\"rssi\":" + String(rssi, 1));
  Serial.print(",\"snr\":" + String(snr, 1));
  Serial.print(",\"seq\":" + String(pkt.seq));
  Serial.print(",\"t\":" + String(millis()));
  Serial.println("}");
}

void updateDisplay() {
  if (millis() - lastDisplay < 500) return;
  lastDisplay = millis();
  oled.clear(); oled.setFont(ArialMT_Plain_10);
  oled.drawString(0, 0, "LIMINAL [" + String(NODE_ID) + "]");
  int row = 0;
  for (int i = 0; i < NUM_NODES; i++) {
    if (i == NODE_ID) continue;
    int y = 16 + row * 16; row++;
    if (!peers[i].active || millis() - peers[i].lastSeen > 5000) {
      oled.drawString(0, y, "Node " + String(i) + ": --");
    } else {
      oled.drawString(0, y, "Node " + String(i) + ": " + String(peers[i].rssi, 0) + "dBm " + String(peers[i].snr, 1) + "dB");
      int barW = map(constrain(peers[i].rssi, -120, -30), -120, -30, 2, 40);
      oled.fillRect(90, y + 2, barW, 8);
    }
  }
  oled.display();
}

void loop() {
  unsigned long now = millis();
  unsigned long elapsed = (now - cycleStart) % CYCLE_MS;
  unsigned long mySlotStart = NODE_ID * SLOT_MS;
  if (elapsed >= mySlotStart && elapsed < mySlotStart + 10) sendPing();
  checkReceive();
  for (int i = 0; i < NUM_NODES; i++)
    if (peers[i].active && now - peers[i].lastSeen > 10000) peers[i].active = false;
  updateDisplay();
  delay(1);
}