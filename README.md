# LCD 16x2
Challenged myself to increase my competency with STM32, I2C, and PlatformIO

## Overview
Take an AdaFruit RGB LCD 16x2 display shield for Arduino and make it
work on a nucleo-144 STM32F413ZH development board.
I happened to have both of these laying around.
Also the nucleo-144 boards have Arduino-compatible sockets.

I have gotten to like Visual Studio Code and have been playing around with the 
Platform IO extension for developing and debugging IoT projects.
I wanted to use PIO instead of the "standard" STM32CubeIDE, Keil, etc., which I felt would add an unwanted learning curve.

I have done an I2C project on ESP32, interfacing with an IMU.
I know that wasn't much, so doing another I2C project on a different plaform
would bolster my I2C chops.

I don't expect the end result to be really useful.
The tradeoff is that a project of limited scope is more likely to get completed.
And the real payoff is learning new ways to do things.

## Uploading with PIO


## Hardware
Arduino shield fits on F413ZH and F429ZI.

+5V
GND
SCL A5
SDA A4

Direct plugin only on UNO
STM32 Nucleo is supposed to be compatible with UNO V3

on nucleo 144
SB138 and SB143 are off
so PB9 SCL and PB8 SDA are NOT connected to A4 A5

ST Zio connectors
SB138, SB143 should be ON for UNO V3 compatibility

Table 13
CN7-2 = D15 = I2C_A_SCL = PB8 = I2C1_SCL
CN7-4 = D14 = I2C_A_SDA = PB9 = I2C1_SDA

But display board also runs SCL SDA to the other corner

SCL A5 PC0 PC3

stmcube i2c

## Components
Adafruit RGB LCD Shield composed of:
- MCP23017 I2C expander
- HD44780LCD module
- PCF 2119 IIC?
- ST7066 Dot Matrix LCD Controller/Driver

### MCP23017
Device address is 0x20, since A2-0 are hardwired to GND

## LCD
HD44780LCD

## What I have learned
- PIO can be used to develop for STM32
- my scope can trigger on I2C missing ACK!
- testing layer by layer is simpler than all at once
- thinking of a problem top down is still useful
- STM32Cube is cool, but seems kind of cumbersome compared to simpler MCUs
- seriously, gotta have solderless breadboards and hookup wire!
- STM32 programming is layered (mbed, HAL/Cube, CMSIS)
- overuse of #defines is evil

## Notes
```
I2C is big-endian over the wire
MCP23017 is big-endian 7-0
ST7066 7-0
but module fips these MCP23017/ST7066
GPB4/DB4
GPB3/DB5
GPB2/DB6
GPB1/DB7
tip use CMSIS __RBIT intrinsic
```

## Links and references
https://community.platformio.org/t/using-stm32cubemx-and-platformio/2611/35

[Using enums for bit masks](https://wiggling-bits.net/using-enum-classes-as-type-safe-bitmasks/)
