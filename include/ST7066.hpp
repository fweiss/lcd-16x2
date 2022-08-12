#pragma once

#include "MCP23017.hpp"

// DB0 - NC
// DB1 - NC
// DB2 - NC
// DB3 - NC
// DB4 - GPB4
// DB5 - GPB3
// DB6 - GPB2
// DB7 - GPB1
// RS - GPB7
// RW - GPB6
// E - GPB5
// (backlight GPB0)

// write instruction 4
// write instruction 8 wait
// write data 8 wait
// read data 8 wait

// GPIOB7 - RS
// GPIOB6 - RW
// GPIOB5 - E
// GPIOB4 - DB4
// GPIOB3 - DB5
// GPIOB2 - DB6
// GPIOB1 - DB7
// GPIOB0 - backlight


class ST7066 {
public:
    ST7066(MCP23017 &mcp23017);
    void write(uint8_t rs, uint8_t data);
    void setup();
    uint8_t readBusyFlag();
    void putc(char c);

    void setCursorOrDisplayShift(uint8_t cursorShift, uint8_t displayShift);
    void setDisplayOnOff(uint8_t bits);
    void setDdramAddress(uint16_t addr);
    void setFunction();
private:
    MCP23017 &mcp23017;

    uint8_t backlight; // needs to be or-ed inot GPIOB


    void waitNotBusy();
    void writeInstruction4(uint8_t);
    void writeInstruction8Wait(uint8_t);
    void writeData8Wait(uint8_t data);
    // void readData8();
    uint8_t read(uint8_t rs);
};
