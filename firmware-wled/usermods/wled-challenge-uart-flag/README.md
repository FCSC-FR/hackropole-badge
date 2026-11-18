# WLED UART challenge usermod

<!--
SPDX-FileCopyrightText: 2026 Hackropole
SPDX-License-Identifier: EUPL-1.2
-->

This usermod sends a flag on ESP32-S3 USB UART at boot.
It also stores a cleartext flag in the firmware, that players can recover using `strings|grep` technique.
