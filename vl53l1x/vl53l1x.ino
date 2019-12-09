#include "ULDAPI/core/VL53L1X_api.c"
#include "ULDAPI/platform/vl53l1_platform.c"
#include "params.h"
#include <i2c_t3.h>

void setup() {
	pinMode(13, OUTPUT);

	Serial.println("Start I2C");
	TOF_I2C.begin();
	Serial.println("Checking BootState");
	uint8_t boot_state = false, status = 0;
	while (!boot_state && !status) {
		status = VL53L1X_BootState(TOF_DEFAULT_ADDRESS, &boot_state);
		delay(2);
	}
	Serial.println("Initializing sensor");
	VL53L1X_SensorInit(TOF_DEFAULT_ADDRESS);
	Serial.println("Starting ranging");
	VL53L1X_StartRanging(TOF_DEFAULT_ADDRESS);
}

void loop() {
	uint8_t data_ready = false;
	while (!data_ready) {
		VL53L1X_CheckForDataReady(TOF_DEFAULT_ADDRESS, &data_ready);
		delay(2);
	}

	uint8_t status;
	uint16_t distance;
	VL53L1X_GetRangeStatus(TOF_DEFAULT_ADDRESS, &status);
	VL53L1X_GetDistance(TOF_DEFAULT_ADDRESS, &distance);
	VL53L1X_ClearInterrupt(TOF_DEFAULT_ADDRESS);

	Serial.print(status);
	Serial.print(',');
	Serial.println(distance);
	delay(1000);
}
