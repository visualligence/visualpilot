#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display{

	Adafruit_SSD1306 adafruit;

public:
	Display()
	: adafruit()
	{
		adafruit.begin( SSD1306_SWITCHCAPVCC, 0x78 );
	}

	void setup()
	{
		adafruit.display();
		delay(2000);
		adafruit.clearDisplay();
	}

	void loop( void ( * draw ) ( void ) )
	{
		draw();
		adafruit.display();
	}

	void text( int x, int y, const char * text )
	{
		//u8g.drawStr( x, y, text );
	}

	void text( int x, int y, int value )
	{
		//char buffer [ 100 ];
		//sprintf( buffer, "%d", value );
		//text( x, y, buffer );
	}

	void h_line( int x, int y, int w )
	{
		adafruit.drawLine( x, y, x + w, y, WHITE );
	}

};


