#pragma once

uint16_t m;
volatile uint16_t s;

void change( void )
{
	if( digitalRead( 7 ) )
		s = 1;//micros() - m;
	else
		m = micros();
}

struct RCChannel
{
	uint8_t pin;
	uint16_t value;

	RCChannel( uint8_t pin = 0 )
	{
		this->value = 0;
		this->pin = pin;

		if( pin != 0 )
		{
			pinMode( pin, INPUT );
			attachInterrupt( digitalPinToInterrupt( pin ), change, CHANGE );
		}
	}

	void read()
	{
		if( pin != 0 && s != 0 )
		{
			value = s;
			s = 0;
		}
	}
};

template<uint8_t num_channels>
class RC
{
	RCChannel rc_channels[ num_channels ];

public:

	RC( uint8_t pins[ num_channels ] )
	{
		for( uint8_t i = 0 ; i < num_channels ; i ++ )
			rc_channels[ i ] = RCChannel( pins[ i ] );
	}

	void loop()
	{
		for( uint8_t i = 0 ; i < num_channels ; i ++ )
			rc_channels[ i ].read();
	}

	void print()
	{
		for( uint8_t i = 0 ; i < num_channels ; i ++ )
		{
			Serial.print( rc_channels[ i ].value );
			Serial.print( "\t" );
		}
	}
};


