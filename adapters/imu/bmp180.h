#pragma once

#include "../i2c_device.h"

class BMP180 : private I2CDevice {

	enum Register{
		ID          = 0xD0,
		CONTROL     = 0xF4,
		DATA        = 0xF6,
		CALIBRATION = 0xAA,
	};
	enum Command{ READ_T = 0x2E, READ_P = 0x34 };
	enum Mode{ LOWPOWER, STANDARD, HIGHRES, ULTRAHIGHRES, NUM_MODES };

	Mode mode;

	int32_t raw_t;
	int32_t raw_p;

	int16_t  ac1;
	int16_t  ac2;
	int16_t  ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t  b1;
	int16_t  b2;
	int16_t  mb;
	int16_t  mc;
	int16_t  md;

public:

	int32_t t_c1;

	int32_t p_pa;
	int32_t p_cm;

	BMP180()
	: I2CDevice( 0x77 )
	{
		// read8( ID ) == 0x55
		mode = LOWPOWER;

		request( CALIBRATION, 22 );

		ac1 = (int16_t) read16_swap();
		ac2 = (int16_t) read16_swap();
		ac3 = (int16_t) read16_swap();
		ac4 =           read16_swap();
		ac5 =           read16_swap();
		ac6 =           read16_swap();
		b1  = (int16_t) read16_swap();
		b2  = (int16_t) read16_swap();
		mb  = (int16_t) read16_swap();
		mc  = (int16_t) read16_swap();
		md  = (int16_t) read16_swap();
	}

	void loop( void )
	{
		read_raw_t();
		read_raw_p();

		raw_to_si();
	}

	void loop_test( void )
	{
		ac1  =    408; //   8131
		ac2  =    -72; //  -1084
		ac3  = -14383; // -14446
		ac4  =  32741; //  33440
		ac5  =  32757; //  24993
		ac6  =  23153; //  19211
		b1   =   6190; //   6515
		b2   =      4; //     39
		mb   = -32768; // -32768
		mc   =  -8711; // -11786
		md   =   2868; //   2824

		mode = LOWPOWER;

		raw_t = 27898;
		raw_p = 23843;

		raw_to_si();
	}

	void print( void )
	{
		Serial.print( t_c1 );
		Serial.print( "\t" );
		Serial.print( p_pa );
		Serial.print( "\t" );
		Serial.print( p_cm );
		Serial.print( "\t" );
	}

private:

	void read_raw_t()
	{
		write( CONTROL, READ_T );
		delay( 5 );

		raw_t = read16_swap( DATA );
	}

	void read_raw_p()
	{
		write( CONTROL, READ_P + ( mode << 6 ) );
		delay( 5 );
		delay( 3 << mode );

		request( DATA, 3 );
		raw_p = (uint32_t) read16_swap() << 8 | read8();
		raw_p >>= ( 8 - mode );
	}

	void raw_to_si( void )
	{
		int32_t x1 = ( raw_t - (int32_t) ac6 ) * ((int32_t) ac5 ) >> 15;
		int32_t x2 = ((int32_t) mc << 11) / ( x1 + (int32_t) md );
		int32_t b5 = x1 + x2;

		t_c1 = ( b5 + 8 ) >> 4;

		int32_t  b6, x3, b3, p;
		uint32_t b4, b7;

		b6 = b5 - 4000;
		x1 = ( b2 * (( b6 * b6 ) >> 12 )) >> 11;
		x2 = ( ac2 * b6 ) >> 11;
		x3 = x1 + x2;
		b3 = (((((int32_t) ac1 ) * 4 + x3 ) << mode ) + 2 ) >> 2;
		x1 = ( ac3 * b6 ) >> 13;
		x2 = ( b1 * (( b6 * b6 ) >> 12 )) >> 16;
		x3 = (( x1 + x2 ) + 2 ) >> 2;
		b4 = ( ac4 * (uint32_t) ( x3 + 32768 )) >> 15;
		b7 = ((uint32_t) ( raw_p - b3 ) * ( 50000 >> mode ) );

		if( b7 < 0x80000000 )
			p = ( b7 << 1 ) / b4;
		else
			p = ( b7 / b4 ) << 1;

		x1 = ( p >> 8 ) * ( p >> 8 );
		x1 = ( x1 * 3038 ) >> 16;
		x2 = ( -7357 * p ) >> 16;

		p_pa = p + (( x1 + x2 + 3791 ) >> 4 );

		float sea_pa = 101325;
		p_cm = 100 * 44330.0 * ( 1.0 - pow( p_pa / sea_pa, 0.1903 ) );
	}

};
