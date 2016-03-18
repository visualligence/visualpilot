#include <Wire.h>

class I2C
{
public:

	static void scan()
	{
		for( int address = 1; address < 127; address ++ )
		{
			Wire.beginTransmission( address );
			if( ! Wire.endTransmission() )
			{
				Serial.print( "0x" );
				if( address < 16 )
					Serial.print( "0" );
				Serial.println( address, HEX );
			}
		}
	}

};
