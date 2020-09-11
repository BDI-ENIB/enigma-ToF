#ifndef TOF_H
#define TOF_H 1

#include "ULDAPI/platform/vl53l1_types.h"
#include "ULDAPI/core/vl53l1_api.h"

#define TOF_GPIO_INTERRUPT 0

class Tof
{
public:
	/**
	 * Initializes the sensor
	 * Use compile switch to choose between gpio interrupt or i2c status read
	 */
	#if TOF_GPIO_INTERRUPT
		Tof(int enable_gpio_id, int interrupt_gpio_id, uint16_t address);
	#else
		Tof(int enable_gpio_id, uint16_t address);
	#endif

	inline uint16_t get_distance() const { return distance; }

	inline void begin() {
		VL53L1X_StartRanging(address);
		ranging = true;
	}

	uint8_t try_refresh_distance();

private:
	#if TOF_GPIO_INTERRUPT
		int interrupt_id;
	#endif

	bool ranging = false;
	uint16_t distance;
	uint16_t address;
	int enable_id;

	inline void set_gpio_mode();
	inline void init_sensor();
};

#endif
