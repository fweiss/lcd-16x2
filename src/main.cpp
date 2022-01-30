/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "MCP23017.hpp"

#define WAIT_TIME_MS 200 
DigitalOut led1(LED1);
DigitalOut led2(LED_RED);
DigitalOut led3(D12);

int main()
{
    I2C i2c(D14, D15);
    i2c.frequency(400000);
    MCP23017 mcp23017(i2c, 0x20);

    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (true)
    {
        led2 = !led2;
        thread_sleep_for(WAIT_TIME_MS);
        // uint8_t d = lcd.update();
        uint8_t d = mcp23017.readXXX();
        mcp23017.backlight(d & 1);
        printf("lcd: %d\n", d);
    }
}
