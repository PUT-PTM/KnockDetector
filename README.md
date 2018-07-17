# KnockDetector

## Overview

Mechanism which protects the door from intruders with a lock that will only open when it hears one of the secret knocks set by authorized users of Android application.

## Description

## Tools

## How to run

| **STM32F4 DISCOVERY** | **Bluetooth module** | 
| ----------------- | ------------------ |
| 5V | VCC |
| GND | GND |
| PC10 | RXD |
| PC11 | TXD |

| **STM32F4 DISCOVERY** | **SD module** | 
| ----------------- | ------------------ |
| 3V | 3V3 |
| GND | GND |
| PB11 | CS |
| PB13 | SCK |
| PB14 | MISO |
| PB15 | MOSI |

| **STM32F4 DISCOVERY** | **H bridge** | **Power Supply**| **Engine**|
| --------------------- | ------------ | --------------- | ----------|
| PA1 | IN1 | - | - | 
| PA2 | IN2 | - | - | 
| - | OUT1 | - | IN1 |
| - | OUT2 | - | IN2 |
| - | 12V | 12V | - |
| 5V | 5V | 5V | - |
| GND | GND | GND | - |

<img src="readme-images/lm358n.jpg"/>


| **STM32F4 DISCOVERY** | **Operational amplifier LM358N** | 
| ----------------- | ------------------ |
| 3V | V+ (8) |
| GND | GND (4) |
| PA0 | Output A (1) |

## How to compile

:one: Clone repository to your machine. <br/>
:two: Connect STM32F4 DISCOVERY to your PC using USB wire. <br/>
:three: Build project in System Workbench for STM32. <br/>
:four: Run project on your STM32F4 from Workbench. <br/>

## Future improvements

### :heavy_check_mark: Final version RELEASED at 8th July 2018
### :warning: This project will no longer be developed

## Attributions

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**

## Credits

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Contractors: Szymon Bandowski, Przemysław Czajka, Jakub Dąbrowski

Supervisor: Tomasz Mańkowski
