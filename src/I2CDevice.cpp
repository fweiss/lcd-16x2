#include "I2CDevice.hpp"

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
    char buf[] { reg, data };
    const bool repeated = false;

    err = i2c.write(addr8bit, buf, sizeof(buf), repeated);
    status |= err ? 0x01 : 0x00;
    if (status) {
        printf("writeRegister: %x\n", status);
    }
}
