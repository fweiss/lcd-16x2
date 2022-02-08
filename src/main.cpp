/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "RGB_LCD_Shield.hpp"

// #include "MCP23017.hpp"
// #include "ST7066.hpp"

#define WAIT_TIME_MS 100 
DigitalOut led2(LED_RED);

int main()
{
    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    I2C i2c(D14, D15);
    // MCP23017 100k 400k 1700k
    i2c.frequency(100 * 1000);

    RgbLcdShield display(i2c, 0x20);

    // MCP23017 mcp23017(i2c, 0x20);
    // ST7066 st7066(mcp23017);
    // st7066.setup();

    display.putcc('H');
    display.putcc('e');
    display.putcc('l');
    display.putcc('l');
    display.putcc('o');
    display.putcc(' ');
    display.putcc('W');
    display.putcc('o');
    display.putcc('r');
    display.putcc('l');
    display.putcc('d');
    display.putcc('!');
    // mcp23017.backlight(0);

    

    while (true)
    {
        led2 = !led2;
        thread_sleep_for(WAIT_TIME_MS);
        // uint8_t d = lcd.update();
        // uint8_t d = mcp23017.readXXX();
        // mcp23017.backlight(d & 1);

        // display.write(0, 0x20);
        // uint8_t busy = st7066.readBusyFlag();
        // printf("busy: %x\n", busy);

        // b = shield.buttons.status();
        // shield.backlight.setColor(b & Shield.Buttons.SELECT);
        // printf("lcd: %d\n", d);
        // printf("lcd: %d\n", 55);

        const uint8_t buttons = display.getButtons();
        if (buttons & 0x01) { // select
            display.setColor(true, true, true);
        } else {
            display.setColor(false, false, false);
        }
    }
}
