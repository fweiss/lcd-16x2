/**
 * @file MCP23017.hpp
 * @author feweiss@gmail.com
 * @brief A wrapper around I2CDevice for symbolic access to the registers of the MCP23017
 * I2C GPIO port expander.
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "I2CDevice.hpp"

// hmm we want to use these locally, so need to undef the globals
// maybe
// #pragma push_macro("MACRONAME")
// #undef MACRONAME
// #pragma pop_macro("MACRONAME")
#undef GPIOA
#undef GPIOB

class MCP23017 : public I2CDevice {
public:
    MCP23017(I2C &i2c, uint8_t addr7);

    enum reg {
        IODIRA, IODIRB,
        IPOLA, IPOLB,
        IOCON = 0x0a,
        GPPUA = 0x0C, GPPUB,
        GPIOA = 0x12, GPIOB,
        OLATA, OLATB
    };
private:
    void setup();
};
