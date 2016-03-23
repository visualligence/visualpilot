#pragma once

#include <Wire.h>

class I2CDevice
{
	uint8_t address;

public:

	I2CDevice( uint8_t address )
	{
		this->address = address;
	}

	void write( uint8_t location, uint8_t data )
	{
		Wire.beginTransmission( address );

		Wire.write( location );
		Wire.write( data );

		Wire.endTransmission();
	}

	void request( uint8_t location, uint8_t size )
	{
		Wire.beginTransmission( address );

		Wire.write( location );

		Wire.endTransmission();

		Wire.requestFrom( address, size );

		while ( Wire.available() < size );
	}

	uint8_t read8()
	{
		return Wire.read();
	}

	uint8_t read8( uint8_t location )
	{
		request( location, 1 );
		return read8();
	}

	uint16_t read16()
	{
		return ( uint16_t )( read8() | ( read8() << 8 ));
	}

	uint16_t read16( uint8_t location )
	{
		request( location, 2 );
		return read16();
	}

	uint16_t read16_swap()
	{
		return ( uint16_t )( ( read8() << 8 ) | read8() );
	}

	uint16_t read16_swap( uint8_t location )
	{
		request( location, 2 );
		return read16_swap();
	}

	static void scan()
	{
		for( uint8_t address = 1; address < 127; address ++ )
		{
			Wire.beginTransmission( address );
			if( Wire.endTransmission() == 0 )
			{
				Serial.print( "0x" );
				if( address < 16 )
					Serial.print( "0" );
				Serial.println( address, HEX );
			}
		}
	}

};
