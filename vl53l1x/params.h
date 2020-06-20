#ifndef TOF_PARAMS
#define TOF_PARAMS 1

#include <i2c_t3.h>

#define TOF_I2C Wire1

// 0x52 >> 1 = 0x29
#define TOF_DEFAULT_ADDRESS 0x29

#define TOF_ADDRESS_1 0x30
#define TOF_ADDRESS_2 0x31

#endif
