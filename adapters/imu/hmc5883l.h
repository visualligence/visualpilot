#pragma once

#include "../../math/v3.h"
#include "../i2c_device.h"

class HMC5883L : public v3<int16_t>, private I2CDevice {

	enum Register{ ID = 0x0A, CONFIGURATION_B = 0x01, MODE = 0x02, X = 0x03 };

public:

	HMC5883L()
	: I2CDevice( 0x1E )
	{
		// read8( ID ) == 0x48  // ..0x37..0x33
		write( MODE, 0x00 );
		write( CONFIGURATION_B, 0xE0 );
	}

	void loop( void )
	{
		request( X, 6 );
		x = read16();
		y = read16();
		z = read16();

		x = x << 8 | x >> 8;
		y = y << 8 | y >> 8;
		z = z << 8 | z >> 8;

	}
};

