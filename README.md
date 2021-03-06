# SimUFC
UFC design for DCS, based on the F-18C Hornet

Display panels originally designed by [OpenHornet](https://github.com/jrsteensen/OpenHornet) and remixed to use .1" headers and multiplexed digits instead of multiplexed half digits.

Displays driven by Holtek HT1632Cs. Board is designed to take Cherry style key switches. I am using Kailh Box Jades, hence the SMD LEDs.

Main assembly is two large PCBs stacked, with the back PCB housing the LED drivers and microcontroller. It is designed to also take a shift register PCB of one of my older designs. It will be replaced later on.

Microcontroller is an STM32 Bluepill.

[![CC BY-NC-SA 4.0][cc-by-nc-sa-shield]][cc-by-nc-sa]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
