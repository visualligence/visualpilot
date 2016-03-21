#pragma once

#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>


template<class T>
struct v3
{
	T x;
	T y;
	T z;

	void print()
	{
		Serial.print( x );
		Serial.print( " " );
		Serial.print( y );
		Serial.print( " " );
		Serial.print( z );
		Serial.print( " " );
	}

};

class Device
{
public:
	virtual void setup() = 0;
	virtual void loop() = 0;
};

class IMU : public Device
{
public:

	v3<float> a;
	v3<float> g;
	v3<float> m;
	uint16_t t;
};

class L3GD20 : public IMU, private Adafruit_L3GD20_Unified {

public:

	L3GD20()
	: Adafruit_L3GD20_Unified( 20 )
	{
	}

	void setup(void)
	{
		enableAutoRange(true);

		/* Initialise the sensor */
		if(!begin())
		{
			/* There was a problem detecting the L3GD20 ... check your connections */
			Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
			while(1);
		}
	}

	void loop(void)
	{
		/* Get a new sensor event */
		sensors_event_t event;
		getEvent(&event);

		/* Display the results (speed is measured in rad/s) */
		g.x = event.gyro.x;
		g.y = event.gyro.y;
		g.z = event.gyro.z;
	}
};
