#include "mbed.h"

class I2CDevice {
public:
    I2CDevice(I2C &i2c, uint8_t address);
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t data);
private:
    I2C &i2c;
    uint8_t addr8bit;
};

I2CDevice::I2CDevice(I2C &i2c, uint8_t address) : i2c(i2c) {
    // MCP23017 100k 400k 1700k
    // frequency(100 * 1000);
    addr8bit = address << 1;
}

uint8_t I2CDevice::readRegister(uint8_t reg) {
    int err;
    char r[1];
    char d[1];

    r[0] = reg;
    err = i2c.write(addr8bit, r, 1, true);
    if (err) printf("write reg err: %d\n", err);
    err = i2c.read(addr8bit, d, 1);
    if (err) printf("read err: %d\n", err);
    return d[0];
}

void I2CDevice::writeRegister(uint8_t reg, uint8_t data) {
    int err;
    char r[1];
    char d[1];

    r[0] = reg;
    d[0] = data;
    err = i2c.write(addr8bit, r, 1, true);
    if (err) printf("write reg err: %d\n", err);
    err = i2c.write(addr8bit, d, 1);
    if (err) printf("read err: %d\n", err);
}
