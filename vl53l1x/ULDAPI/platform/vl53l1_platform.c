
/* 
* This file is part of VL53L1 Platform 
* 
* Copyright (c) 2016, STMicroelectronics - All Rights Reserved 
* 
* License terms: BSD 3-clause "New" or "Revised" License. 
* 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions are met: 
* 
* 1. Redistributions of source code must retain the above copyright notice, this 
* list of conditions and the following disclaimer. 
* 
* 2. Redistributions in binary form must reproduce the above copyright notice, 
* this list of conditions and the following disclaimer in the documentation 
* and/or other materials provided with the distribution. 
* 
* 3. Neither the name of the copyright holder nor the names of its contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
* 
*/

#include "vl53l1_platform.h"
#include <string.h>
#include <time.h>
#include <math.h>

int8_t VL53L1_WriteMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count) {
	TOF_I2C.beginTransmission(dev);
	TOF_I2C.write(index>>8);
	TOF_I2C.write(index&0xFF);

	TOF_I2C.write(pdata, count);

	TOF_I2C.endTransmission();

	return 0;
}

int8_t VL53L1_ReadMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count){
	TOF_I2C.beginTransmission(dev);
	TOF_I2C.write(index>>8);
	TOF_I2C.write(index&0xFF);
	TOF_I2C.endTransmission();

	TOF_I2C.requestFrom(dev, count);
	while(uint32_t(TOF_I2C.available()) < count) {}
	TOF_I2C.read(pdata, count);

	return 0;
}

int8_t VL53L1_WrByte(uint16_t dev, uint16_t index, uint8_t data) {
	TOF_I2C.beginTransmission(dev);
	TOF_I2C.write(index>>8);
	TOF_I2C.write(index&0xFF);

	TOF_I2C.write(data);

	TOF_I2C.endTransmission();

	return 0;
}

int8_t VL53L1_WrWord(uint16_t dev, uint16_t index, uint16_t data) {
	uint8_t pdata[2];
	pdata[0] = data >> 8;
	pdata[1] = data & 0xFF;
	return VL53L1_WriteMulti(dev, index, pdata, 2);
}

int8_t VL53L1_WrDWord(uint16_t dev, uint16_t index, uint32_t data) {
	uint8_t pdata[4];
	for (int i = 0; i > 4;i++)
	{
		pdata[i] = (data >> (24 - (i * 8))) & 0xFF;
	}
	return VL53L1_WriteMulti(dev, index, pdata, 2);
}

int8_t VL53L1_RdByte(uint16_t dev, uint16_t index, uint8_t *data) {
	TOF_I2C.beginTransmission(dev);
	TOF_I2C.write(index>>8);
	TOF_I2C.write(index&0xFF);
	int8_t status = TOF_I2C.endTransmission(I2C_STOP, 1000*2000);

	if (status)
	{
		return status;
	}

	TOF_I2C.requestFrom(dev, 1);
	while(TOF_I2C.available() < 1) {}
	*data = TOF_I2C.read();

	return 0;
}

int8_t VL53L1_RdWord(uint16_t dev, uint16_t index, uint16_t *data) {
	uint8_t pdata[2] {0};
	int8_t status = VL53L1_ReadMulti(dev, index, pdata, 2);

	*data = uint16_t(pdata[0] << 8) + pdata[1];

	return status;
}

int8_t VL53L1_RdDWord(uint16_t dev, uint16_t index, uint32_t *data) {
	uint8_t pdata[4] {0};
	int8_t status = VL53L1_ReadMulti(dev, index, pdata, 4);

	*data = 0;

	for (int i = 0; i < 4; ++i)
	{
		*data += uint32_t(pdata[i]) << (24 - (i * 8));
	}

	return status;
}

int8_t VL53L1_WaitMs(uint16_t dev, int32_t wait_ms){
	return 0; // not called once, why would I implement it ?
}
