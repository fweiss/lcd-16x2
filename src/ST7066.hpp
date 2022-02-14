#ifndef ST7066_H
#define ST7066_H

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

ST7066::ST7066(MCP23017 &mcp23017) : mcp23017(mcp23017) {
    backlight = 0x01;
    mcp23017.writeRegister(mcp23017.OLATB, backlight);
    mcp23017.writeRegister(mcp23017.IODIRB, 0x1e);
}

// initialize for 4-bit
// big endian
// only needed if power up init fails
// but needed because power up init sets 8-bit mode
void ST7066::setup() {
    thread_sleep_for(15);
    writeInstruction4(0x03);
    thread_sleep_for(4);
    writeInstruction4(0x03);
    // 100 us
    writeInstruction4(0x03);
    writeInstruction4(0x02); // function set 4-bit
    writeInstruction8Wait(0x20 | 0x02 | 0x00); // function set: lines, font size
    writeInstruction8Wait(0x08); // display off
    writeInstruction8Wait(0x01); // display clear
    writeInstruction8Wait(0x04 | 0x00 | 0x00 ); // address inc/dec, display shift
}

void ST7066::write(uint8_t rs, uint8_t data) {
    uint8_t reverse = __RBIT(data) >> 27;
    const uint8_t enable = 0x20;

    // construct a buf 76543210
    // where 
    // 7 is RS 0=instruction, 1=data
    // 6 is RW 0=write, 1=read
    // 5 is E
    // 4 is DB4
    // 3 is DB5
    // 2 is DB6
    // 1 is DB7
    // 0 is backlight blue
    uint8_t buf = rs | (reverse & 0x1e) | backlight;
    mcp23017.writeRegister(mcp23017.IODIRB, 0x00); // all bit output
    mcp23017.writeRegister(mcp23017.OLATB, buf);
    mcp23017.writeRegister(mcp23017.OLATB, buf | enable); // strobe
    mcp23017.writeRegister(mcp23017.OLATB, buf); // end strobe
    mcp23017.writeRegister(mcp23017.IODIRB, 0x1e); // all bits output except 4-1
}

uint8_t ST7066::read(uint8_t rsx) {
    const uint8_t rs = 0x00; // instruction register
    const uint8_t rw = 0x40; // read
    const uint8_t enable = 0x20;

    uint8_t buf = rs | rw | backlight;

    mcp23017.writeRegister(mcp23017.IODIRB, 0x1e); // all bits ouput except 4-1
    mcp23017.writeRegister(mcp23017.GPPUB, 0x1e); // pullup 4-1

    mcp23017.writeRegister(mcp23017.OLATB, buf);
    mcp23017.writeRegister(mcp23017.OLATB, buf | enable); // strobe
    uint32_t data = mcp23017.readRegister(mcp23017.GPIOB);
    mcp23017.writeRegister(mcp23017.OLATB, buf); // end strobe

    return __RBIT(data << 27);
}

uint8_t ST7066::readBusyFlag() {
    // no busy check needed
    // "read" from the instruction register
    uint8_t data = read(0x40); // RS=instruction
    return data >> 7;
}

// wait busy, must be low to perform next instruction
void ST7066::waitNotBusy() {
    uint8_t busyFlag;
    do {
        busyFlag = readBusyFlag();
    } while (busyFlag);
}

void ST7066::writeInstruction4(uint8_t instruction) {
    // uint32_t reverse = __RBIT((uint32_t)instruction);
    // mcp23017.writeRegister(mcp23017.GPIOB, reverse >> 28);
    write(0x00, instruction);
}

// 
void ST7066::writeInstruction8Wait(uint8_t instruction) {
    waitNotBusy();
    write(0x00, (instruction >> 4) & 0x0f);
    write(0x00, instruction & 0x0f);
    // uint32_t reversed = __RBIT((uint32_t)instruction);
    // // each nibble with reversed bits
    // mcp23017.writeRegister(mcp23017.GPIOB, reversed >> 28); // most significant nibble first
    // mcp23017.writeRegister(mcp23017.GPIOB, reversed >> 24);
}

// void ST7066::writeData8Wait(uint8_t data) {
//     waitNotBusy();
//     const uint8_t rs = 0x80; // data
//     write(rs, (data >> 4) & 0x0f);
//     write(rs, data & 0x0f);
// }

void ST7066::writeData8Wait(uint8_t data) {
    const uint8_t rs = 0x80; // data register
    // eight bit data b7-b0 reversed in 32 bit b31-b24
    // shift left 1 to align with GPIO output to st7066 data
    const uint32_t reverse = __RBIT(data);
    uint8_t buf = ((reverse >> (24-1)) & 0x1e) | rs;
    uint8_t buf2 = ((reverse >> (28-1)) & 0x1e) | rs;
    const uint8_t enable = 0x20;
    waitNotBusy();
    mcp23017.writeRegister(mcp23017.IODIRB, 0x00); // all bit output
    mcp23017.writeRegister(mcp23017.OLATB, buf); // setup rw and rs
    mcp23017.writeRegister(mcp23017.OLATB, buf | enable);
    mcp23017.writeRegister(mcp23017.OLATB, buf); // hold data
    mcp23017.writeRegister(mcp23017.OLATB, buf2 | enable);
    mcp23017.writeRegister(mcp23017.OLATB, buf2); // hold data
    mcp23017.writeRegister(mcp23017.IODIRB, 0x1e); // all bit output except b4-1
}

void ST7066::putc(char c) {
    writeInstruction8Wait(0x08 | 0x04); // display: on
    writeInstruction8Wait(0x20 | 0x00 | 0x08); // function: 8 bit, 2 line
    // writeInstruction8Wait(0x20 | 0x00 | 0x00 | 0x04); // function: 8 bit, 1 line, 5x11 font
    writeInstruction8Wait(0x04 | 0x02); // entry mode set: move cursor right
    writeData8Wait(c);
}

void ST7066::setDisplayOnOff(uint8_t bits) {
    const uint8_t instruction = 0x08 | (bits & 0x7);
    writeInstruction8Wait(instruction);
}

void ST7066::setFunction() {
    const uint8_t instruction = 0x20;
    writeInstruction8Wait(instruction);
}

void ST7066::setDdramAddress(uint16_t addr) {
    const uint8_t instruction = 0x80 | (addr & 0x7f);
    writeInstruction8Wait(instruction);
}

#endif // ST7066_H
