# Brailletouch - Affordable Braille Device for the Visually Impaired and Deafblind
[![en](https://img.shields.io/badge/lang-es-red.svg)](README.es.md)

## Table of Contents
- [Overview](#overview)
- [Project Components](#project-components)
  - [Physical Device Design](#1-physical-device-design)
  - [Electronics and Firmware](#2-electronics-and-firmware)
  - [Interface with Screen Readers](#3-interface-with-screen-readers)
- [Required Components](#required-components)
- [Reference Images](#reference-images)
- [Get Involved](#get-involved)

## Overview

Brailletouch is an open-source project dedicated to creating an affordable braille device, making assistive technology accessible to everyone. Traditional braille displays often come with a hefty price tag, ranging from $1,200 to $6,000 USD. Our mission is to reduce these costs by up to 90%, enabling visually impaired and deafblind individuals to read, write braille, and use computers or mobile devices efficiently and quietly.

Whether you're a developer, a curious mind, or someone who wants to make a difference, we invite you to join our community on [GitHub](https://github.com/brailletouch) and help us shape the future of Brailletouch.

## Project Components

Brailletouch comprises three essential components:

### 1. Physical Device Design

- Braille Cell
- Matrix of 40 Touch Sensors
- Buttons
- Assembly Box

### 2. Electronics and Firmware

- ESP32 Microcontroller
- Power Source Selection (Batteries or Jack)
- PWM Controller
- PCF8574 Multiplexer/Demultiplexer (8 Channels)
- Arduino IDE Code (.ino)

### 3. Interface with Screen Readers

- NVDA (Windows)
- BrailleBack (Android)
- BRLTTY (Linux, Android, Windows)

## Required Components

To build Brailletouch, you'll need the following components:

- 1 ESP32 Microcontroller
- 4 Servo Motors
- 4 PCF8574 Multiplexers/Demultiplexers (8 Channels)
- 1 Braille Cell (developed with 4 servo motors; any braille cell type will work)
- Assembly Box
- PWM Controller (for simultaneous pin control and faster readings)
- Keyboard buttons and cables
- Optional: A screen for text monitoring
- Optional: PS/2 connector for keyboard input (for deafblind individuals)
- 1 Printed Circuit Board for touch sensors (still in development to control 40 positions with only 9 pins available on ESP32)

## Reference Images

![image](https://user-images.githubusercontent.com/9951014/143519725-5d493c91-513b-4640-ae0b-aba3ea0b435c.png)

![image](https://github.com/discapacidad5/brailletouch/blob/main/esp32-pca9685-hookup.jpg) [Reference](http://www.esp32learning.com/code/esp32-and-a-pcf8574-expander-example.php) [PCF8574 library](https://www.arduino.cc/reference/en/libraries/pcf8574-library/)

![image](https://github.com/discapacidad5/brailletouch/blob/main/modulo-expansor-io-pcf8574.jpg)

![image](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%201.png)

![image](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%20celda%20braile.png)

![image](https://github.com/discapacidad5/brailletouch/blob/main/diagrama%201%20de%20coneciones%20brailletouch.png)

## Get Involved

We welcome contributions from developers, designers, testers, and anyone interested in helping us make Brailletouch a reality. Follow these steps to get started:

### 1. Fork the Repository

Start by forking this repository to your own GitHub account. This will create a copy of the project that you can work on without affecting the main repository.

![Fork](https://docs.github.com/assets/images/help/repository/fork_button.jpg)

### 2. Clone the Repository

Next, clone the forked repository to your local machine. Open a terminal and use the following command, replacing `[your-username]` with your GitHub username:

```bash
git clone https://github.com/[your-username]/Brailletouch.git
