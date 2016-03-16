#include "SSD1306.h"

class Display{

	SSD1306 display;

public:
	Display()
	: display( 0x3C )
	{
	}

	void setup()
	{
		display.init();
		display.flipScreenVertically();
	}

	void loop( void ( * draw ) ( void ) )
	{
  		display.clear();
		draw();
		display.display();
	}

	void text( int x, int y, const char * text )
	{
		display.setTextAlignment( TEXT_ALIGN_LEFT );
		display.setFont( ArialMT_Plain_10 );
		display.drawString( x, y, text );
	}

	void text( int x, int y, int value )
	{
		char buffer [ 100 ];
		sprintf( buffer, "%d", value );
		text( x, y, buffer );
	}

	void h_line( int x, int y, int w )
	{
		for( int i_x = x; i_x < x + w; i_x ++ )
			display.setPixel( i_x, y );
	}

};


