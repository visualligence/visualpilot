#pragma once

class RCChannel
{
public:
	virtual void print() = 0;
};


template<int pin>
class RCChannelPin : public RCChannel
{
public:

	volatile static uint32_t last_value;
	volatile static uint32_t last_high;

	void static rising( void )
	{
		last_high = micros();
	}

	void static falling( void )
	{
		last_value = micros() - last_high;
	}

	RCChannelPin()
	{
		pinMode( pin, INPUT );
		attachInterrupt( digitalPinToInterrupt( pin ), rising,  RISING  );
		attachInterrupt( digitalPinToInterrupt( pin ), falling, FALLING );
	}

	void print()
	{
		Serial.print( last_value );
		Serial.print( "\t" );
	}
};

template<int pin>
volatile uint32_t RCChannelPin<pin>::last_value = 0;

template<int pin>
volatile uint32_t RCChannelPin<pin>::last_high = 0;
