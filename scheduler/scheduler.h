#pragma once

class Scheduler
{
	uint32_t last_start;
	uint32_t last_end;

	Scheduler()
	: last_start( 0 )
	: last_end( 1 )
	{
	}

	void loop( void )
	{
		last_start = last_end;
		last_end = micros();
	}

	void print( void )
	{
		Serial.print( 1000000 / ( last_end - last_start ) );
	}

};
