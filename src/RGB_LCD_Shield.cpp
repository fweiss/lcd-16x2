#include "RGB_LCD_Shield.hpp"

RgbLcdShield::RgbLcdShield(I2C &i2c, uint8_t addr7) : MCP23017(i2c, addr7), st7066(*this) {

        writeRegister(OLATA, 0xc0); // backlight off
        writeRegister(GPPUA, 0x1f); // 4-0 button inputs
        writeRegister(IPOLA, 0x1f); // buttons are inverted open-drain
        writeRegister(IODIRA, 0x3f); // 4-0 button inputs, 7-6 backlight outputs, 5 ?

        writeRegister(OLATB, 0x01); // backlight off
        writeRegister(GPPUB, 0x1e); // 4-1 possibly ST7066 inputs
        writeRegister(IODIRB, 0x1e); // leave ST7066 data pins as inputs for now

        st7066.setup();
}

void RgbLcdShield::setColor(bool red, bool green, bool blue) {
    const bool color = red || green || blue; // all for now
    // active low
    writeRegister(OLATA, color ? 0x00 : 0xc0);
    writeRegister(OLATB, color ? 0x00 : 0x01);
}

void RgbLcdShield::putcc(char c) {
    st7066.putc(c);
}

uint8_t RgbLcdShield::getButtons() {
    // active low set in IPOLA
    return readRegister(GPIOA) & 0x1f;
}

void RgbLcdShield::setPosition(uint8_t pos, uint8_t line) {
    // todo check bounds
    const uint8_t addr = 0x40 | 3;
    st7066.setDdramAddress(addr);
}

void RgbLcdShield::shiftCursorAndDisplay(ShiftDirection direction) {
    st7066.setCursorOrDisplayShift(0x08, direction);
}
