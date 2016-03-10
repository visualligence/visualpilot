#include <U8glib.h> // https://github.com/olikraus/u8glib/wiki

class Display{

	U8GLIB_SSD1306_128X64 u8g;

public:
	// 	u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI
	// 	u8g(U8G_I2C_OPT_NO_ACK);	// Display which does not send AC

	Display()
	: u8g( U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0 ) // I2C / TWI
	{
	}

	void setup()
	{
		u8g.setFont( u8g_font_6x10 );
		u8g.setFontRefHeightExtendedText();
		u8g.setDefaultForegroundColor();
		u8g.setFontPosTop();
		u8g.firstPage();
	}

	void loop( void ( * draw ) ( void ) )
	{
		u8g.firstPage();
		do {
			draw();
		} while( u8g.nextPage() );
	}

	void text( int x, int y, const char * text )
	{
		u8g.drawStr( x, y, text );
	}

	void text( int x, int y, int value )
	{
		char buffer [ 100 ];
		sprintf( buffer, "%d", value );
		text( x, y, buffer );
	}

	void h_line( int x, int y, int w )
	{
		u8g.drawHLine( x, y, w );
	}

};


