#ifndef TOF_H
#define TOF_H 1

#include "ULDAPI/platform/vl53l1_types.h"
#include "ULDAPI/core/vl53l1_api.h"

class Tof
{
public:
	Tof(int enable_gpio_id, int interrupt_gpio_id, uint16_t address);

	inline uint16_t get_distance() const { return distance; }

	inline void begin() {
		VL53L1X_StartRanging(address);
		ranging = true;
	}

	uint8_t try_refresh_distance();

private:
	uint16_t distance;
	uint16_t address;
	int enable_id, interrupt_id;
	bool ranging = false;

	inline void set_gpio_mode();
	inline void init_sensor();
};

#endif
