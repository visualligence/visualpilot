#include "./adapters/displays/ssd1306_128x64.h"
#include "./adapters/pwm/i2c_12bit.h"
#include "./adapters/imu/nunchuk.h"

uint8_t loop_number = 0;

uint16_t loop_start = 0;
uint16_t loop_end = 1;

Display display = Display();
PWM pwm = PWM();
IMU imu = IMU();

void setup(void) {
	Wire.setClock( 400000L );

	display.setup();
	pwm.setup();
	imu.setup();
}

void draw(void) {
	display.h_line( 0,  0, loop_number % 128 );

	int line_height = 8;

	display.h_line( 0, 1 * line_height, map( imu.a.x,  0, 1024, 0, 127 ) );
	display.h_line( 0, 2 * line_height, map( imu.a.y,  0, 1024, 0, 127 ) );
	display.h_line( 0, 3 * line_height, map( imu.a.z,  0, 1024, 0, 127 ) );

	display.text(  0, 35, "mfps" );
	display.text( 25, 35, 1000000L / ( loop_end - loop_start ) );
}

void loop(void) {
	imu.update();
	display.loop( draw );

	loop_number ++;
	loop_start = loop_end;
	loop_end = millis();
}


