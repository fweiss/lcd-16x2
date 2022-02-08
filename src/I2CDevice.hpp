#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

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

I2CDevice::I2CDevice(I2C &i2c, uint8_t address) : i2c(i2c) {
    addr8bit = address << 1;
}

uint8_t I2CDevice::readRegister(uint8_t reg) {
    status = 0;
    int err;
    char r[1];
    char d[1];

    r[0] = reg;
    err = i2c.write(addr8bit, r, 1, true);
    status |= err ? 0x01 : 0x00;
    err = i2c.read(addr8bit, d, 1);
    status |= err ? 0x04 : 0x00;
    if (status) {
        printf("readRegister: %x\n", status);
    }
    return d[0];
}

void I2CDevice::writeRegister(uint8_t reg, uint8_t data) {
    status = 0;
    int err;
    char r[2];
    char d[1];

    r[0] = reg;r[1] = data;
    d[0] = data;
    err = i2c.write(addr8bit, r, 2, false);
    status |= err ? 0x01 : 0x00;
    // err = i2c.write(addr8bit, d, 1);
    // status |= err ? 0x02 : 0x00;
    if (status) {
        printf("writeRegister: %x\n", status);
    }
}

#endif // I2C_DEVICE_H
