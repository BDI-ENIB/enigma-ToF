#include "pcf8575.h"
#include "params.h"

PCF8575::PCF8575(uint8_t address):
address{address}
{}

uint8_t PCF8575::read(uint16_t &value) {
	TOF_I2C.requestFrom(address, 2);
	uint16_t msb = TOF_I2C.readByte();
	uint16_t lsb = TOF_I2C.readByte();
	value = (msb << 8) | lsb;

	return 0;
}

uint8_t PCF8575::write(uint16_t value) {
	TOF_I2C.beginTransmission(address);
	TOF_I2C.write(value>>8);
	TOF_I2C.write(value&0xFF);

	return TOF_I2C.endTransmission();
}

uint8_t PCF8575::get_last_high_index(int &index) {
	uint16_t value;
	auto status = read(value);

	if (status)
		return status;

	index = -1;
	while (value) {
		index++;
		value = value >> 1;
	}

	return 0;
}
