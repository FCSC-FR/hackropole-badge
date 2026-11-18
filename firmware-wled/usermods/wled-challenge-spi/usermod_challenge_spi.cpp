// SPDX-FileCopyrightText: 2026 Hackropole
// SPDX-License-Identifier: EUPL-1.2

#include "mbedtls/aes.h"
#include "mbedtls/cipher.h"
#include "wled.h"
#include <SPI.h>

// "Blackhoodie{s3cr3t_d3c0d3d_3f0f621f}\n\0";
const char _flag[] PROGMEM = {
    0xe5, 0xf1, 0x7e, 0x4a, 0x6e, 0x9d, 0xff, 0xd9, 0x14, 0xb8, 0x53, 0x10,
    0x2a, 0x87, 0xe0, 0x64, 0x48, 0x13, 0x82, 0xc5, 0xf,  0x73, 0xe,  0x32,
    0xc2, 0x15, 0xa1, 0x39, 0x79, 0x27, 0x95, 0x87, 0x5f, 0x3,  0xd0, 0xb,
    0xc9, 0xfb, 0xcd, 0xc9, 0xdb, 0x7f, 0x8a, 0xc9, 0x98, 0xc0, 0x98, 0x5c};
uint8_t flagDecSPI[48] = {0};

static const int spiClk = 1000000; // 1 MHz
SPIClass *spi = NULL;

class MyChallengeSpiUsermod : public Usermod {
private:
  unsigned long lastTime = 0;

public:
  void setup() override {
    spi = new SPIClass(SPI);
    // Only 11 and 12 are exposed
    spi->begin(11, 13, 12, 14); // SCLK, MISO, MOSI, SS

    // Decrypt flag once, this makes sure the player don't trivialy dump the flag from a dump
    unsigned char iv[] = {0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    const unsigned char key[] = "82e468a6fc23fbf8";
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 48, iv,
                          (const unsigned char *)FPSTR(_flag), flagDecSPI);
    mbedtls_aes_free(&aes);
  }

  void loop() override {
    // if usermod is called during strip updating just exit
    if (strip.isUpdating())
      return;

    // emit flag every 1s
    if (millis() - lastTime > 1000) {
      spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
      for (uint i = 0; i < 48; i++) {
        spi->transfer(flagDecSPI[i]);
      }
      spi->endTransaction();

      lastTime = millis();
    }
  }
};

static MyChallengeSpiUsermod spi_usermod;
REGISTER_USERMOD(spi_usermod);
