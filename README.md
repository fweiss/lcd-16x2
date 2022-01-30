# 16x2

## Hardware
Arduino shield fits on F413ZH

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
- Adafruit RGB LCD Shield
- MCP23017 I2C expander
- HD44780LCD module
- PCF 2119 IIC?
- ST7066 Dot Matrix LCD Controller/Driver

### MCP23017
Device address is 0x20, since A2-0 are hardwaired to GND

## LCD
HD44780LCD

## Links and references
https://community.platformio.org/t/using-stm32cubemx-and-platformio/2611/35

https://learn.adafruit.com/rgb-lcd-shield/downloads
