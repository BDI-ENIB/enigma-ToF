#include "ULDAPI/core/vl53l1_api.c"
#include "ULDAPI/platform/vl53l1_platform.c"
#include "params.h"
#include "tof.h"
#include <i2c_t3.h>

Tof* tof1 = nullptr;

void setup() {
	pinMode(13, OUTPUT);

	Serial.println("Start I2C");
	TOF_I2C.begin();
	
	Serial.println("Initializing sensor");
	tof1 = new Tof(33, 0, TOF_ADDRESS_1);

	Serial.println("Starting ranging");
	tof1->begin();
}

void loop() {
	static uint8_t status1 = 0
	status1 = tof1->try_refresh_distance();

	Serial.print(status1);
	Serial.print(',');
	Serial.println(tof1->get_distance());


	delay(1000);
}
