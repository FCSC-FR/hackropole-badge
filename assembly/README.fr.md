# Assemblage du badge Hackropole

<!--
SPDX-FileCopyrightText: 2025 Hackropole
SPDX-License-Identifier: CC-BY-4.0
-->

Vous venez de recevoir votre tout nouveau badge Hackropole et vous souhaitez
l'assembler ? Vous pouvez suivre ce guide pour assembler le badge.

> [!WARNING]
> Le FCSC/Hackropole ne peut être tenu responsable si vous vous faites mal
> pendant le montage, cassez quelque chose ou blessez votre chat.
> Soyez prudent avec les fers à souder, ils sont chauds, émettent des fumées et
> peuvent être très dangereux s'ils sont mal utilisés !

## Composants requis

Bien que le PCB permette une certaine flexibilité de modding pour exprimer votre
créativité, nous recommandons vivement de vous procurer les éléments suivants
afin de disposer d'une base sur laquelle vous appuyer :

- **1x [ESP32-S3-Zero](https://www.waveshare.com/wiki/ESP32-S3-Zero) sans les broches pré-soudés**,
  aussi parfois appelé "ESP32-S3 Mini".
  Cette carte est disponible sur [la boutique Waveshare](https://www.waveshare.com/product/arduino/boards-kits/esp32-s3/esp32-s3-zero.htm),
  mais vous pouvez également la trouver chez d'autres revendeurs comme par exemple
  [ThePiHut](https://thepihut.com/products/esp32-s3-zero-mini-development-board),
  ou sur des marketplaces internationaux (ceux commençant par "Ali").
  Attention, **n'achetez pas les variantes "SuperMini"** car leur brochage est
  différent et ne fonctionnera pas !
- **8x WS2812B LED, au format 5050SMD**. Ces LED peuvent être achetés en grande
  quantité (100 pièces et plus) pour une somme modique dans certains magasins internationaux.
- Un fer à souder (si possible asservi en température) et un peu de fil à souder.
  Les petits fers à souder USB-C tels que [ceux pris en charge par IronOS](https://ralim.github.io/IronOS/)
  sont adaptés pour les débutants.

Composants **facultatifs** pour modifier votre carte ultérieurement et exprimer
votre créativité :

- Un tour de cou pour porter le circuit imprimé comme un badge de conférence
  (et avoir la classe !).
- Une batterie externe USB pour rendre le badge autonome.
- 2x entretoises en nylon M2 6mm (écrou, boulon et pilier hexagonal) pour
  construire une boîte-lampe avec 2 badges.
- Quelques capteurs compatibles Qwiic et un câble Qwiic à souder sur les pads
  GP14/GP15/3V3/GND. Qui a dit que votre badge ne devrait pas mesurer la
  lumière ambiante ? :D

Pour plus d'inspiration, vous pouvez consulter [la page des usermods WLED](https://github.com/wled/WLED/blob/main/usermods/readme.md).

## Assemblage de l'ESP32-S3-Zero et des LED

Commencez par nettoyer la carte, en particulier les pads sur lesquels vous allez
souder les composants.
N'utilisez pas d'eau pour le nettoyage, car elle pourrait être corrosive.
Préférez l'**alcool isopropylique**.

> [!AVERTISSEMENT]
> Les fumées de soudure contiennent un nombre élevé de particules.
> Vous devez toujours souder avec un extracteur de fumées en marche,
ou au moins dans un endroit très ventilé.

Soudez l'ESP32-S3-Zero en mettant un peu de soudure sur la broche 7, en vous
assurant que le composant est correctement placé, puis en mettant de la soudure
sur la broche opposée (5V) pour verrouiller la position. Commencez ensuite à
souder toutes les broches restantes une par une.
Lorsque le résultat obtenu est satisfaisant, nettoyez les résidus de flux
restant sur le circuit imprimé.

![ESP32-S3-Zero soudé](./esp32s3_solder.jpg)

Utilisez une technique similaire pour chaque LED WS2812B, mais diminuez
légèrement la température du fer à souder, car le plastique des LED peut
facilement fondre.

Vous pouvez également vous référer à la vidéo suivante qui montre le processus
de soudage : [esp32s3_soldering.webm](./esp32s3_soldering.webm)

## Après avoir assemblé la carte

Pour vérifier si la carte fonctionne, vous pouvez flasher le micrologiciel WLED.
Référez-vous à [../firmware-wled/](../firmware-wled/README.fr.md) pour flasher
et de configurer le micrologiciel.
