#pragma once

#include "mbed.h"

class I2CDevice {
public:
    I2CDevice(I2C &i2c, uint8_t address);
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t data);
    uint8_t status;
private:
    I2C &i2c;
    uint8_t addr8bit;
};
