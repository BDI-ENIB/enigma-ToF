#include "ULDAPI/core/vl53l1_api.c"
#include "ULDAPI/platform/vl53l1_platform.c"
#include "params.h"
#include "tof.h"
#include <i2c_t3.h>

Tof* tof1 = nullptr;
Tof* tof2 = nullptr;

void setup() {
	pinMode(13, OUTPUT);

	Serial.println("Start I2C");
	TOF_I2C.begin();
	
	Serial.println("Initializing sensor");
	tof1 = new Tof(33, 0, TOF_ADDRESS_1);
	tof2 = new Tof(34, 0, TOF_ADDRESS_2);

	Serial.println("Starting ranging");
	tof1->begin();
	tof2->begin();
}

void loop() {
	static uint8_t status1 = 0
	static uint8_t status2 = 0;
	status1 = tof1->try_refresh_distance();
	status2 = tof2->try_refresh_distance();

	Serial.print(status1);
	Serial.print(',');
	Serial.print(status2);
	Serial.print(',');
	Serial.print(tof1->get_distance());
	Serial.print(',');
	Serial.println(tof2->get_distance());


	delay(1000);
}
