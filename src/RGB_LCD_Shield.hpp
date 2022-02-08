/**
 * @file RGB_LCD_Shield.hpp
 * @author Frank Weiss (feweiss@gmail.com)
 * @brief A composite for the AdaFruit RGB LCD Shield
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "MCP23017.hpp"
#include "ST7066.hpp"

class RgbLcdShield : private MCP23017 {
public:
    RgbLcdShield(I2C &i2c, uint8_t addr7);

    void setColor(bool red, bool green, bool blue);
    void putcc(char c);
    uint8_t getButtons();
private:
    ST7066 st7066;
};

RgbLcdShield::RgbLcdShield(I2C &i2c, uint8_t addr7) : MCP23017(i2c, addr7), st7066(*this) {

        writeRegister(OLATA, 0xc0); // backlight off
        writeRegister(GPPUA, 0x1f); // 4-0 button inputs
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
    // active low
    return (~readRegister(GPIOA)) & 0x1f;
}