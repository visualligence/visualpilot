#pragma once

#include "../../math/v3.h"
#include "../i2c_device.h"

class ADXL345 : public v3<int16_t>, private I2CDevice {

	enum Register{ ID = 0x00, POWER_SAVE = 0x2D, X = 0x32, Y = 0x34, Z = 0x36 };

public:

	ADXL345()
	: I2CDevice( 0x53 )
	{
		// read8( ID ) == 0xE5
		write( POWER_SAVE, 0x08 );
	}

	void loop( void )
	{
		request( X, 6 );
		x = read16();
		y = read16();
		z = read16();
	}
};
