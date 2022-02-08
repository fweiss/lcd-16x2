/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "MCP23017.hpp"
#include "ST7066.hpp"

#define WAIT_TIME_MS 50
DigitalOut led2(LED_RED);

void udelay(uint32_t delay) {
    delay = 10;
    volatile uint32_t x;
    while (delay-- > 0) x = delay;
}

int main()
{
    I2C i2c(D14, D15);
    i2c.frequency(100000);
    MCP23017 mcp23017(i2c, 0x20);

    printf("This is the mcp23017 test running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    // uint8_t iocon = mcp23017.readRegister(mcp23017.IOCON);
    // printf("iocon: %x\n", iocon);

    // mcp23017.writeRegister(mcp23017.OLATB, 0x00);
    // since reset pin is not used, ensure correct
    // mcp23017.writeRegister(mcp23017.IOCON, 0x20); // no sequenctial

    mcp23017.writeRegister(mcp23017.OLATB, 0x00);
    mcp23017.writeRegister(mcp23017.IODIRB, 0x1e);

    mcp23017.writeRegister(mcp23017.OLATB, 0xe0);
    mcp23017.writeRegister(mcp23017.OLATB, 0x00);


    // mcp23017.writeRegister(0x1a, 0xe0);
    // mcp23017.writeRegister(0x10, 0x1e);

    while (true)
    {
        led2 = !led2;
        thread_sleep_for(WAIT_TIME_MS);
        // uint8_t d = lcd.update();
        // uint8_t d = mcp23017.readXXX();
        // mcp23017.backlight(d & 1);

        // st7066.write(0, 0x20);
        // st7066.readBusyFlag();

        // testing
        // mcp23017.readRegister(mcp23017.OLATB);
        // for (int i=0; i<0; i++) {
        //     mcp23017.writeRegister(mcp23017.IODIRB, 0x1f);
        //     mcp23017.writeRegister(mcp23017.OLATB, 0x00);
        //     thread_sleep_for(2);
        //     mcp23017.writeRegister(mcp23017.OLATB, 0x20);  
        // }

        // mcp23017.writeRegister(mcp23017.OLATB, 0xe0);
        // udelay(1);
        // mcp23017.writeRegister(mcp23017.OLATB, 0x00);
        // mcp23017.writeRegister(mcp23017.OLATB, 0xe0);
        // udelay(1);
        // mcp23017.writeRegister(mcp23017.OLATB, 0x00);
        // mcp23017.writeRegister(mcp23017.OLATB, 0xe0);
        // udelay(1);
        // mcp23017.writeRegister(mcp23017.OLATB, 0x00);
        // mcp23017.writeRegister(mcp23017.OLATB, 0xe0);
        // udelay(1);
        // mcp23017.writeRegister(mcp23017.OLATB, 0x00);
        // mcp23017.writeRegister(mcp23017.OLATB, 0xe0);
        // udelay(1);
        // mcp23017.writeRegister(mcp23017.OLATB, 0x00);

    }
}
