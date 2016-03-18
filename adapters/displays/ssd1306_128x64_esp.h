#include "SSD1306.h"

class Display : private SSD1306 {

public:
	enum Align
	{
		LEFT = TEXT_ALIGN_LEFT,
		RIGHT = TEXT_ALIGN_RIGHT
	};

	Display()
	: SSD1306( 0x3C )
	{
	}

	void setup()
	{
		sendInitCommands();
		resetDisplay();
		flipScreenVertically();
	}

	void loop( void ( * draw ) ( void ) )
	{
 		clear();
		draw();
		display();
	}

	void text( uint8_t x, uint8_t y, const char * text, Align align = LEFT )
	{
		setTextAlignment( align );
		setFont( ArialMT_Plain_10 );
		drawString( x, y, text );
	}

	void text( uint8_t x, uint8_t y, uint32_t value, Align align = LEFT )
	{
		char buffer [ 100 ];
		sprintf( buffer, "%d", value );
		text( x, y, buffer, align );
	}

	void pixel( uint8_t x, uint8_t y )
	{
		setPixel( x, y );
	}

	void h_line( uint8_t x, uint8_t y, uint8_t w )
	{
		line( x, y, x+w, y );
		//for( uint8_t i_x = x; i_x < x + w; i_x ++ )
		//	pixel( i_x, y );
	}

	void line( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 )
	{
		uint8_t tmp;
		uint8_t x,y;
		uint8_t dx, dy;
		int8_t err;
		int8_t ystep;

		uint8_t swapxy = 0;

		/* no BBX intersection check at the moment, should be added... */

		if ( x1 > x2 ) dx = x1-x2; else dx = x2-x1;
		if ( y1 > y2 ) dy = y1-y2; else dy = y2-y1;

		if ( dy > dx )
		{
			swapxy = 1;
			tmp = dx; dx = dy; dy = tmp;
			tmp = x1; x1 = y1; y1 = tmp;
			tmp = x2; x2 = y2; y2 = tmp;
		}
		if ( x1 > x2 )
		{
			tmp = x1; x1 = x2; x2 = tmp;
			tmp = y1; y1 = y2; y2 = tmp;
		}
		err = dx >> 1;
		if ( y2 > y1 ) ystep = 1; else ystep = -1;
		y = y1;

		if ( x2 == 0xff )
			x2--;

		for( x = x1; x <= x2; x++ )
		{
			if ( swapxy == 0 )
				pixel( x, y );
			else
				pixel( y, x );

			err -= (uint8_t) dy;
			if ( err < 0 )
			{
				y += (uint8_t) ystep;
				err += (uint8_t) dx;
			}
		}
	}

};


