#ifndef PCF8575_H
#define PCF8575_H 1

#include <cstdint>

class PCF8575
{
	uint8_t address;

public:
	PCF8575(uint8_t addr);
	
	uint8_t write(uint16_t value);

	uint8_t read(uint16_t &value);

	uint8_t get_last_high_index(int &index);
};

#endif
