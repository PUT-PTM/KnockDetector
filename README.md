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
| PA1 | IN1 |  |  |  | 
| PA2 | IN2 |  |  |  | 
|  | OUT1 |  |  | IN1 |
|  | OUT2 |  |  | IN2 |
|  | 12V | 12V |  |  |
| 5V | 5V | 5V |  |  |
| GND | GND | GND |  |  |

## How to compile

## Future improvements

## Attributions

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**

## Credits

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Contractors: Jakub Dąbrowski, Szymon Bandowski, Przemysław Czajka

Supervisor: Tomasz Mańkowski
