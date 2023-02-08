/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "RGB_LCD_Shield.hpp"

#define WAIT_TIME_MS 100 

// #if PLATFORM == ststm32
// DigitalOut led2(LED_RED);
// #endif
// #if PLATFORM == nordicnrf52
// DigitalOut led2(LED1);
// #endif

// this depends on the platform
// use PIO build_flags in platformio.ini
DigitalOut led2(ACTIVITY_LED);

// mbed i2c pins
PinName const sda = D14;
PinName const scl = D15;

// this is fixed by the AdaFruit RGB LCD Shield
int const mcp23017_I2C_Address = 0x20;

int main() {
    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    I2C i2c(sda, scl);
    // MCP23017 100k 400k ok, 1700k not
    // nRF52 couldn't handle 400k issue #1
    i2c.frequency(100 * 1000);

    RgbLcdShield display(i2c, mcp23017_I2C_Address);

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

    // arbitrary, not magic positions
    // just to test setPosition()
    display.setPosition(3, 1);
    display.putcc('G');

    while (true) {
        led2 = !led2;
        thread_sleep_for(WAIT_TIME_MS);

        const uint8_t buttons = display.getButtons();
        if (not (buttons & RgbLcdShield::ButtonMask::select)) {
            display.setColor(true, true, true);
        } else {
            display.setColor(false, false, false);
        }

        if (buttons & RgbLcdShield::ButtonMask::left) {
            display.shiftCursorAndDisplay(RgbLcdShield::ShiftDirection::leftShift);
        }
        if (buttons & RgbLcdShield::ButtonMask::right) {
            display.shiftCursorAndDisplay(RgbLcdShield::ShiftDirection::rightShift);
        }
    }
}
