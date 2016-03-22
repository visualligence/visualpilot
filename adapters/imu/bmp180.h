#pragma once

#include "../i2c_device.h"

class BMP180 : private I2CDevice {

	enum Register{
		ID      = 0xD0,
		CONTROL = 0xF4,
		DATA    = 0xF6,
		ADDRESS_AC1 = 0xAA,
		ADDRESS_AC2 = 0xAC,
		ADDRESS_AC3 = 0xAE,
		ADDRESS_AC4 = 0xB0,
		ADDRESS_AC5 = 0xB2,
		ADDRESS_AC6 = 0xB4,
		ADDRESS_B1  = 0xB6,
		ADDRESS_B2  = 0xB8,
		ADDRESS_MB  = 0xBA,
		ADDRESS_MC  = 0xBC,
		ADDRESS_MD  = 0xBE
	};
	enum Command{ READ_T = 0x2E, READ_P = 0x34 };

	enum Mode{ LOWPOWER, STANDARD, HIGHRES, ULTRAHIGHRES, NUM_MODES };
	uint8_t delays_by_mode[ NUM_MODES ] = { 5, 8, 14, 26 };

	Mode mode;

	int32_t raw_t;
	int32_t raw_p;

	int16_t  _AC1;
	int16_t  _AC2;
	int16_t  _AC3;
	uint16_t _AC4;
	uint16_t _AC5;
	uint16_t _AC6;
	int16_t  _B1;
	int16_t  _B2;
	int16_t  _MB;
	int16_t  _MC;
	int16_t  _MD;

public:

	int32_t t_c1;

	int32_t p_pa;
	int32_t p_cm;

	BMP180()
	: I2CDevice( 0x77 )
	{
		// read8( ID ) == 0x55
		mode = LOWPOWER;

		_AC1 = (int16_t) read16( ADDRESS_AC1 );
		_AC2 = (int16_t) read16( ADDRESS_AC2 );
		_AC3 = (int16_t) read16( ADDRESS_AC3 );
		_AC4 =           read16( ADDRESS_AC4 );
		_AC5 =           read16( ADDRESS_AC5 );
		_AC6 =           read16( ADDRESS_AC6 );
		_B1  = (int16_t) read16( ADDRESS_B1 );
		_B2  = (int16_t) read16( ADDRESS_B2 );
		_MB  = (int16_t) read16( ADDRESS_MB );
		_MC  = (int16_t) read16( ADDRESS_MC );
		_MD  = (int16_t) read16( ADDRESS_MD );

		Serial.println( _AC1 );
		Serial.println( _AC2 );
		Serial.println( _AC3 );
		Serial.println( _AC4 );
		Serial.println( _AC5 );
		Serial.println( _AC6 );
		Serial.println( _B1  );
		Serial.println( _B2  );
		Serial.println( _MB  );
		Serial.println( _MC  );
		Serial.println( _MD  );
	}

	void loop( void )
	{
		read_raw_t();
		read_raw_p();
		raw_to_si();
	}

	void print( void )
	{
		Serial.print( t_c1 );
		Serial.print( p_pa );
	}

private:

	void read_raw_t()
	{
		write( CONTROL, READ_T );
		raw_t = read16( DATA );
	}

	void read_raw_p()
	{
		write( CONTROL, READ_P + ( mode << 6 ) );
		delay( delays_by_mode[ mode ] );

		request( DATA, 3 );
		raw_p = (uint32_t) read16() << 8 | read8();
		raw_p >>= ( 8 - mode );
	}

	void raw_to_si( void )
	{
		int32_t _X1 = ( raw_t - (int32_t) _AC6 ) * ((int32_t) _AC5 ) >> 15;
		int32_t _X2 = ((int32_t) _MC << 11) / ( _X1 + (int32_t) _MD );
		int32_t _B5 = _X1 + _X2;

		t_c1 = ( _B5 + 8 ) >> 4;

		int32_t _B6, _X3, _B3, __P;
		uint32_t _B4, _B7;

		/* Pressure compensation */
		_B6 = _B5 - 4000;
		_X1 = ( _B2 * (( _B6 * _B6 ) >> 12 )) >> 11;
		_X2 = ( _AC2 * _B6) >> 11;
		_X3 = _X1 + _X2;
		_B3 = (((((int32_t) _AC1 ) * 4 + _X3 ) << mode ) + 2 ) >> 2;
		_X1 = ( _AC3 * _B6 ) >> 13;
		_X2 = ( _B1 * (( _B6 * _B6 ) >> 12)) >> 16;
		_X3 = (( _X1 + _X2 ) + 2) >> 2;
		_B4 = ( _AC4 * (uint32_t) ( _X3 + 32768 )) >> 15;
		_B7 = ((uint32_t) ( raw_p - _B3 ) * ( 50000 >> mode ) );

		if( _B7 < 0x80000000 )
			__P = ( _B7 << 1 ) / _B4;
		else
			__P = ( _B7 / _B4 ) << 1;

		_X1 = ( __P >> 8 ) * ( __P >> 8 );
		_X1 = ( _X1 * 3038 ) >> 16;
		_X2 = ( -7357 * __P ) >> 16;
		p_pa = __P + (( _X1 + _X2 + 3791 ) >> 4 );
	}

};
