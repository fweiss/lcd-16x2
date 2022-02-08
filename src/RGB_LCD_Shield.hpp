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
// #include "ST7066.hpp"

// class Buttons {

// };

// class Backlight {

// };

// class Display {

// };

class RgbLcdShield : private MCP23017 {
public:
    RgbLcdShield(I2C &i2c, uint8_t addr7);

    // Buttons buttons;
    // Backlight backlight;
    // Display display;

    void setColor(bool red, bool green, bool blue);
    void putcc(char c);
private:
};

RgbLcdShield::RgbLcdShield(I2C &i2c, uint8_t addr7) : MCP23017(i2c, addr7) {

}

void RgbLcdShield::setColor(bool red, bool green, bool blue) {

}

void RgbLcdShield::putcc(char c) {

}