#pragma once

template<class T>
struct v3
{
	T x;
	T y;
	T z;

	void print()
	{
		Serial.print( x );
		Serial.print( "\t" );
		Serial.print( y );
		Serial.print( "\t" );
		Serial.print( z );
		Serial.print( "\t" );
	}

};
