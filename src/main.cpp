/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "RGB_LCD_Shield.hpp"

#define WAIT_TIME_MS 100 
DigitalOut led2(LED_RED);

int main()
{
    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    I2C i2c(D14, D15);
    // MCP23017 100k 400k 1700k
    i2c.frequency(100 * 1000);

    RgbLcdShield display(i2c, 0x20);

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

    display.setPosition(3, 1);
    display.putcc('G');

    while (true)
    {
        led2 = !led2;
        thread_sleep_for(WAIT_TIME_MS);

        const uint8_t buttons = display.getButtons();
        if (buttons & RgbLcdShield::ButtonMask::select) {
            display.setColor(true, true, true);
        } else {
            display.setColor(false, false, false);
        }
        if (buttons & RgbLcdShield::ButtonMask::left) {
            display.shiftCursorAndDisplay(RgbLcdShield::ShiftDirection::right);
        }
    }
}
