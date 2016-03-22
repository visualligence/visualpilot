#pragma once

#include "../../math/v3.h"
#include "../i2c_device.h"

class L3GD20 : public v3<int16_t>, private I2CDevice {

	enum Register{ ID = 0x0F, CONTROL_1 = 0x20, CONTROL_4 = 0x23, X = 0x28 };

public:

	L3GD20()
	: I2CDevice( 0x69 )
	{
		// read8( ID ) == 0xD3 // or 0xD4 or 0xD7
		write( CONTROL_1, 0x00 );
		write( CONTROL_1, 0x0F );
		write( CONTROL_4, 0x20 );
	}

	void loop( void )
	{
		request( X | 0x80, 6 );
		x = read16();
		y = read16();
		z = read16();
	}
};
