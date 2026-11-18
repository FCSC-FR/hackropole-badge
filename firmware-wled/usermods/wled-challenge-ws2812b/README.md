# WLED WS2812B challenge usermod

<!--
SPDX-FileCopyrightText: 2026 Hackropole
SPDX-License-Identifier: EUPL-1.2
-->

This usermod adds hidden WS2812B onto the main WLED LED strip.
The player can probe the signal output of the 8-th LED of the board.
Then, they can either use a logic analyzer that can decode WS2812B out-of-the-box,
or implement a small Python decoder by studying how this protocol works.
