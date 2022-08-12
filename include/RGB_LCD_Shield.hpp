/**
 * @file RGB_LCD_Shield.hpp
 * @author Frank Weiss (feweiss@gmail.com)
 * @brief A composite/facade for the AdaFruit RGB LCD Shield
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "MCP23017.hpp"
#include "ST7066.hpp"

class RgbLcdShield : private MCP23017 {
public:
    RgbLcdShield(I2C &i2c, uint8_t addr7);

    enum ButtonMask : uint8_t {
        select = 0x01,
        right = 0x02,
        down = 0x04,
        up = 0x08,
        left = 0x10
    };
    enum ShiftDirection {
        leftShift = 0,
        rightShift = 0x04
    };
    
    uint8_t getButtons();

    void setColor(bool red, bool green, bool blue);
    void putcc(char c);
    void setPosition(uint8_t pos, uint8_t line);
    void shiftCursorAndDisplay(ShiftDirection direction);

private:
    ST7066 st7066;
};
