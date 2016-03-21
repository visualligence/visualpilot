#pragma once

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */

class LSM303_A : public IMU, private Adafruit_LSM303_Accel_Unified {

public:

	LSM303_A()
	: Adafruit_LSM303_Accel_Unified( 54321 )
	{
	}

	void setup(void)
	{
		enableAutoRange(true);

		/* Initialise the sensor */
		if( !begin() )
		{
			/* There was a problem detecting the LSM303 ... check your connections */
			Serial.println( "Ooops, no LSM303 (Accelerometer) detected ... Check your wiring!" );
			while( 1 );
		}

		sensor_t sensor;
		getSensor(&sensor);
		Serial.println("------------------------------------");
		Serial.print  ("Sensor:       "); Serial.println(sensor.name);
		Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
		Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
		Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
		Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
		Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
		Serial.println("------------------------------------");
		Serial.println("");
		delay(500);
	}

	void loop( void )
	{
		/* Get a new sensor event */
		sensors_event_t event;
		getEvent( &event );

		/* Display the results (speed is measured in rad/s) */
		a.x = event.acceleration.x;
		a.y = event.acceleration.y;
		a.z = event.acceleration.z;
	}
};
