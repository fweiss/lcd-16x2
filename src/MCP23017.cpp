#include "MCP23017.hpp"

MCP23017::MCP23017(I2C &i2c, uint8_t addr7) : I2CDevice(i2c, addr7) {
}
