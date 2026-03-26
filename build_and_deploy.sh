#!/bin/bash
# ═══════════════════════════════════════════════════════════
# LIMINAL — Build firmware (Heltec V3) & prepare for web flash
# ═══════════════════════════════════════════════════════════
set -e

echo ""
echo "═══════════════════════════════════════════"
echo "  LIMINAL — Building for Heltec V3"
echo "  (ESP32-S3 + SX1262)"
echo "═══════════════════════════════════════════"
echo ""

pio run

echo ""
echo "Build complete. Copying binaries..."
echo ""

LABELS=("A" "B" "C" "D")

for i in 0 1 2 3; do
  ENV="node${i}"
  SRC=".pio/build/${ENV}"
  DEST="docs/firmware/node${i}"

  mkdir -p "${DEST}"

  # Firmware
  cp "${SRC}/firmware.bin" "${DEST}/firmware.bin"
  echo "  Node ${i} (${LABELS[$i]}): firmware.bin"

  # Bootloader — ESP32-S3 offset is 0x0000
  if [ -f "${SRC}/bootloader.bin" ]; then
    cp "${SRC}/bootloader.bin" "${DEST}/bootloader.bin"
  else
    BL=$(find ${HOME}/.platformio/packages/framework-arduinoespressif32 \
         -path "*/esp32s3*" -name "bootloader_dio_80m.bin" -print -quit 2>/dev/null)
    if [ -n "${BL}" ]; then
      cp "${BL}" "${DEST}/bootloader.bin"
    fi
  fi

  # Partitions
  if [ -f "${SRC}/partitions.bin" ]; then
    cp "${SRC}/partitions.bin" "${DEST}/partitions.bin"
  fi

  # boot_app0.bin
  BOOT_APP0=$(find ${HOME}/.platformio -name "boot_app0.bin" -print -quit 2>/dev/null)
  if [ -n "${BOOT_APP0}" ]; then
    cp "${BOOT_APP0}" "${DEST}/boot_app0.bin"
  fi

  # ─── MANIFEST ──────────────────────────────────────────
  # ESP32-S3 bootloader offset = 0x0000 (not 0x1000 like ESP32)
  cat > "${DEST}/manifest.json" << MANIFEST
{
  "name": "LIMINAL Node ${i} (${LABELS[$i]})",
  "version": "$(date +%Y.%m.%d)",
  "new_install_prompt_erase": true,
  "builds": [
    {
      "chipFamily": "ESP32-S3",
      "parts": [
        { "path": "bootloader.bin", "offset": 0 },
        { "path": "partitions.bin", "offset": 32768 },
        { "path": "boot_app0.bin", "offset": 57344 },
        { "path": "firmware.bin", "offset": 65536 }
      ]
    }
  ]
}
MANIFEST

  echo "  Node ${i} (${LABELS[$i]}): manifest.json (ESP32-S3)"
  echo ""
done

echo "═══════════════════════════════════════════"
echo "  Done! Binaries ready in docs/firmware/"
echo "═══════════════════════════════════════════"
echo ""
echo "  Next:"
echo "    git add ."
echo "    git commit -m \"Add V3 firmware binaries\""
echo "    git push"
echo ""

echo "  Binary sizes:"
for i in 0 1 2 3; do
  SIZE=$(du -h "docs/firmware/node${i}/firmware.bin" | cut -f1)
  echo "    Node ${i}: ${SIZE}"
done
echo ""