#include "tof.h"
#include "params.h"

Tof::Tof(int enable_gpio_id, int interrupt_gpio_id, uint16_t address):
distance{}, address{address}, enable_id{enable_gpio_id}, interrupt_id{interrupt_gpio_id} 
{
	#if SERIAL_DEBUG
		Serial.print("Initializing sensor at enable ");
		Serial.println(enable_gpio_id);
	#endif
	set_gpio_mode();
	#if SERIAL_DEBUG
		Serial.println("init");
	#endif
	init_sensor();
}

void Tof::set_gpio_mode() {
	pinMode(enable_id, OUTPUT);
	pinMode(interrupt_id, INPUT);
}

void Tof::init_sensor() {
	// Disable sensor
	#if SERIAL_DEBUG
		Serial.println("disable");
	#endif
	digitalWrite(enable_id, LOW);
	delay(50);

	// Enable sensor
	#if SERIAL_DEBUG
		Serial.println("enable");
	#endif
	digitalWrite(enable_id, HIGH);

	// Check boot state
	#if SERIAL_DEBUG
		Serial.println("boot");
	#endif
	uint8_t boot_state = false, status = 0;
	while (!boot_state || status) {
		status = VL53L1X_BootState(TOF_DEFAULT_ADDRESS, &boot_state);
		#if SERIAL_DEBUG
			Serial.print("status: ");
			Serial.print(status);
			Serial.print(" boot_state: ");
			Serial.println(boot_state);
		#endif
		delay(2);
	}

	// Initialize sensor
	#if SERIAL_DEBUG
		Serial.println("init");
	#endif
	VL53L1X_SensorInit(TOF_DEFAULT_ADDRESS);

	// Change address
	#if SERIAL_DEBUG
		Serial.println("addr");
	#endif
	VL53L1X_SetI2CAddress(TOF_DEFAULT_ADDRESS, address << 1);

	// Set distance mode
	#if SERIAL_DEBUG
		Serial.println("dist");
	#endif
	VL53L1X_SetDistanceMode(address, 1); // 1=short, 2=long
}
/**
 * Possible return values:
 * 0: no error
 * 1: sigma failure
 * 2: signal failure
 * 3: not refreshed
 * 4: out of bounds
 * 5: not ranging
 * 7: wraparound
 */
uint8_t Tof::try_refresh_distance() {
	if (not ranging)
		return 5;

	uint8_t data_ready = false, status = 3;

	VL53L1X_CheckForDataReady(address, &data_ready);
	if (data_ready) {
		VL53L1X_GetRangeStatus(address, &status);
		VL53L1X_GetDistance(address, &distance);
		VL53L1X_ClearInterrupt(address);
	}
	if (status == 7) {
		distance += 1300;
	}
	return status;
}
