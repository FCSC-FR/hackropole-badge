// SPDX-FileCopyrightText: 2026 Hackropole
// SPDX-License-Identifier: EUPL-1.2

#include "mbedtls/aes.h"
#include "mbedtls/cipher.h"
#include "wled.h"

// "Blackhoodie{m0r3_L3Ds!}\0";
const char _flag[] PROGMEM = {0x87, 0x54, 0xa,  0x5c, 0x6a, 0xe7, 0x44, 0x7f,
                              0xa3, 0xb1, 0x2f, 0x88, 0x3b, 0x18, 0x43, 0xe4,
                              0x10, 0x29, 0x93, 0xe6, 0xf7, 0x37, 0x70, 0x3,
                              0x9a, 0x2e, 0xb1, 0x86, 0xb4, 0x8f, 0x50, 0xa1};
uint8_t flagDecWs[32] = {0};

class MyChallengeWs2812bUsermod : public Usermod {
public:
  void setup() override {
    // Decrypt flag once, this makes sure the player don't trivialy dump the
    // flag from a dump
    unsigned char iv[] = {0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    const unsigned char key[] = "8f302a96b0e30db6";
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 32, iv,
                          (const unsigned char *)FPSTR(_flag), flagDecWs);
    mbedtls_aes_free(&aes);
  }

  void loop() override {}

  void handleOverlayDraw() override {
    // for each char
    for (uint i = 0; i < 24; i += 1) {
      uint8_t c = flagDecWs[i];
      // for each bit
      for (uint j = 0; j < 8; j += 1) {
        if (c & (1 << (7 - j))) { // on
          strip.setPixelColor(8 + i * 8 + j, RGBW32(0, 0, 255, 0));
        } else { // off
          strip.setPixelColor(8 + i * 8 + j, RGBW32(0, 0, 0, 0));
        }
      }
    }
  }
};

static MyChallengeWs2812bUsermod ws2812b_usermod;
REGISTER_USERMOD(ws2812b_usermod);
