#pragma once

class HCSR04 {
public:
	virtual void print() = 0;
	virtual void loop() = 0;
};

template<int trigger_pin, int echo_pin>
class HCSR04Pins : public HCSR04
{
public:

	volatile static uint32_t last_value_mm;
	volatile static uint32_t last_echo_high;

	HCSR04Pins()
	{
		pinMode( trigger_pin, OUTPUT );
		pinMode( echo_pin, INPUT );
		attachInterrupt( digitalPinToInterrupt( echo_pin ), echo, FALLING );
	}

	void static trigger()
	{
		digitalWrite( trigger_pin, LOW );
		delayMicroseconds( 10 );
		digitalWrite( trigger_pin, HIGH );
		delayMicroseconds( 10 );
		digitalWrite( trigger_pin, LOW );
	}

	void static echo( void )
	{
		last_value_mm = ( micros() - last_echo_high - 10 ) * 10 / 58;

		Serial.println( last_value_mm );
	}

	void loop()
	{
		if( micros() - last_echo_high >= 6000 )
		{
			last_echo_high = micros();
			trigger();
		}
	}

	void print()
	{
		Serial.print( last_value_mm );
		Serial.print( "\t" );
	}
};

template<int trigger_pin, int echo_pin>
volatile uint32_t HCSR04Pins<trigger_pin,echo_pin>::last_value_mm = 0;

template<int trigger_pin, int echo_pin>
volatile uint32_t HCSR04Pins<trigger_pin,echo_pin>::last_echo_high = 0;
