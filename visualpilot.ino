#include "./adapters/displays/ssd1306_128x64.h"
#include "./adapters/pwm/i2c_12bit.h"

uint8_t loop_number = 0;

Display display = Display();
PWM pwm = PWM();

void setup(void) {
	display.setup();
	pwm.setup();
}

void draw(void) {
	display.text( 0, 5, loop_number );

	display.h_line( 0,  0, loop_number % 128 );
	display.h_line( 0, 63, loop_number % 128 );
}

void loop(void) {
	loop_number ++;

	pwm.set_angle( 0, loop_number % 2 ? 0 : 180 );
	display.loop( draw );

	delay( 1000 );
}


