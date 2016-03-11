#include <Wire.h>

#define ADDRESS 0x52

template<class T>
struct v3
{
	T x;
	T y;
	T z;
};

class IMU
{
	void send(byte data, byte location)
	{
		Wire.beginTransmission( ADDRESS );

		Wire.write( location );
		Wire.write( data );

		Wire.endTransmission();

		delay( 10 );
	}

public:

	v3<uint16_t> a;

	void setup()
	{
		Wire.begin();

		send( 0x55, 0xF0 );
		send( 0x00, 0xFB );
	}

	void update()
	{
		send( 0x00, 0x00 );

		delay( 50 );

		Wire.requestFrom( ADDRESS, 6 );

		byte values[ 6 ];
		for( byte i = 0; Wire.available() ; i++ )
			values[ i ] = Wire.read();

		a.x = (values[2] << 2) | ((values[5] >> 2) & 3);
		a.y = (values[3] << 2) | ((values[5] >> 4) & 3);
		a.z = (values[4] << 2) | ((values[5] >> 6) & 3);

		// jx = values[0]; // 255
		// jy = values[1]; // 255
		// bc = !((values[5] >> 0) & 1); // 0-1
		// bz = !((values[5] >> 1) & 1); // 0-1
	}

};
