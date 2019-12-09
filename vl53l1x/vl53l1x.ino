#include "ULDAPI/core/vl53l1_api.c"
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
	Serial.println("Changing address");
	VL53L1X_SetI2CAddress(TOF_DEFAULT_ADDRESS, TOF_ADDRESS_1 << 1);
	Serial.println("Starting ranging");
	VL53L1X_StartRanging(TOF_ADDRESS_1);
}

void loop() {
	uint8_t data_ready = false;
	while (!data_ready) {
		VL53L1X_CheckForDataReady(TOF_ADDRESS_1, &data_ready);
		delay(2);
	}

	uint8_t status;
	uint16_t distance;
	VL53L1X_GetRangeStatus(TOF_ADDRESS_1, &status);
	VL53L1X_GetDistance(TOF_ADDRESS_1, &distance);
	VL53L1X_ClearInterrupt(TOF_ADDRESS_1);

	Serial.print(status);
	Serial.print(',');
	Serial.println(distance);
	delay(1000);
}
