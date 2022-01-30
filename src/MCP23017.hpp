#include "mbed.h"
#include "I2CDevice.hpp"

// hmm we want to use these locally, so need to undef the globals
// maybe
// #pragma push_macro("MACRONAME")
// #undef MACRONAME
// #pragma pop_macro("MACRONAME")
#undef GPIOA
#undef GPIOB

class MCP23017 : I2CDevice {
public:
    MCP23017(I2C &i2c, uint8_t addr7);

    int readXXX();
    void backlight(uint8_t color);

    enum reg {
        IODIRA, IODIRB, 
        GPPUA = 0x0C, GPPUB,
        GPIOA = 0X12, GPIOB,
    };
private:
    void setup();
};

MCP23017::MCP23017(I2C &i2c, uint8_t addr7) : I2CDevice(i2c, addr7) {
    setup();
}

void MCP23017::setup() {
    // set pullups for buttons on PORTA bits 43210
    writeRegister(GPPUA, 0x1f);
    // set output for backlight
    writeRegister(IODIRB, 0xFE); // A0
    writeRegister(IODIRA, 0x3f); // B7, B6
}

int MCP23017::readXXX() {
    return readRegister(GPIOA);
}

void MCP23017::backlight(uint8_t color) {
    writeRegister(GPIOB, 0x01);
    writeRegister(GPIOA, color ? 0xc0 : 0x00);
}