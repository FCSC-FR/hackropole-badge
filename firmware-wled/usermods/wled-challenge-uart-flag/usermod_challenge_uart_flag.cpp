// SPDX-FileCopyrightText: 2026 Hackropole
// SPDX-License-Identifier: EUPL-1.2

#include "mbedtls/aes.h"
#include "mbedtls/cipher.h"
#include "wled.h"

class MyChallengeUartFlagUsermod : public Usermod {
private:
  static const char _flag1[];
  static const char _flag2[];

public:
  void setup() override {
    Serial.println("init...\n");
    delay(1000);
    Serial.println("Hello from the UART!");

    // Decrypt and print flag once, this makes sure the player don't trivialy
    // dump the flag from a dump
    unsigned char iv[] = {0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    const unsigned char key[] = "e0206a52a7cc4b61";
    unsigned char output[64] = {0};
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 64, iv,
                          (const unsigned char *)FPSTR(_flag1), output);
    mbedtls_aes_free(&aes);
    Serial.println(F(output));

    Serial.println(
        F("This badge contains multiple challenges. Each challenge contains a "
          "flag to recover, will you fetch all the flag?"));
    Serial.println(F("Maybe you should take a look at GPIO14/GPIO15, or maybe "
                     "dump the firmware and look for familiar strings?"));
    Serial.println(F("Good luck and have fun! ^-^\r\n**************\r\n\r\n"));
  }

  void loop() override {}

  /*
   * Add flag to /json/info part of the JSON API, in clear so string grep can
   * find it
   */
  void addToJsonInfo(JsonObject &root) override {
    JsonObject flag = root[F("flag")];
    if (flag.isNull())
      flag = root.createNestedObject(F("flag"));
    JsonArray temp = flag.createNestedArray(F("value"));
    temp.add(FPSTR(_flag2));
  }
};

// "Blackhoodie{Hello_its_me!_3ce33a4d139e338a22e7fda2d87ed251s54}\n\0";
const char MyChallengeUartFlagUsermod::_flag1[] PROGMEM = {
    0x43, 0x34, 0x80, 0xbd, 0x22, 0x85, 0x92, 0xf9, 0x6f, 0xa8, 0x16, 0x20,
    0x65, 0xf,  0x34, 0x5a, 0x3,  0xf5, 0x98, 0xd0, 0x1,  0xd0, 0x27, 0x3d,
    0xd1, 0xdd, 0x7b, 0x79, 0xe8, 0xe9, 0x87, 0x9b, 0x34, 0x96, 0xe0, 0x19,
    0x4c, 0xa7, 0xe3, 0xe5, 0x49, 0x9a, 0xa5, 0xfc, 0xf8, 0xba, 0xfa, 0xff,
    0x36, 0xe9, 0xad, 0xee, 0xf2, 0x55, 0xba, 0x28, 0x67, 0xfb, 0x79, 0xcb,
    0x46, 0x6f, 0x5a, 0x9b, 0x16, 0xbc, 0x19, 0x0,  0x40, 0x1b, 0xf9, 0x7a,
    0x31, 0x86, 0x9d, 0x22, 0x6a, 0x24, 0x55, 0x11};

// flag stored in clear, so that the player can trivialy dump it
const char MyChallengeUartFlagUsermod::_flag2[] PROGMEM =
    "Blackhoodie{look_at_/json/info_368db0113419a5b92601181cdd146d77}";

static MyChallengeUartFlagUsermod uart_flag_usermod;
REGISTER_USERMOD(uart_flag_usermod);
