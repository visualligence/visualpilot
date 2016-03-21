#pragma once

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */

class LSM303_M : public IMU, private Adafruit_LSM303_Mag_Unified {

public:

	LSM303_M()
	: Adafruit_LSM303_Mag_Unified( 12345 )
	{
	}

	void setup(void)
	{
		enableAutoRange(true);

		/* Initialise the sensor */
		if( !begin() )
		{
			/* There was a problem detecting the LSM303 ... check your connections */
			Serial.println( "Ooops, no LSM303 (Magnetometer) detected ... Check your wiring!" );
			while( 1 );
		}

		sensor_t sensor;
		getSensor(&sensor);
		Serial.println("------------------------------------");
		Serial.print  ("Sensor:       "); Serial.println(sensor.name);
		Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
		Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
		Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
		Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
		Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
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
		m.x = event.magnetic.x;
		m.y = event.magnetic.y;
		m.z = event.magnetic.z;
	}
};
