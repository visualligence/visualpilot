//#include "./adapters/i2c.h"

#include "./adapters/displays/ssd1306_128x64_esp.h"
#include "./adapters/pwm/i2c_12bit.h"
#include "./adapters/imu/nunchuk.h"

uint32_t loop_number = 0;

uint16_t loop_start = 0;
uint16_t loop_end = 1;
uint16_t loop_duration = 1;

Display display = Display();
IMU imu = IMU();
PWM pwm = PWM();

void setup(void) {
	Wire.begin();
	Wire.setClock( 300000L );

	display.setup();
	imu.setup();
	pwm.setup();
}

void draw(void) {
	display.h_line( 0, 63, loop_number % 128 );

	display.text( 128,  0, loop_number, Display::RIGHT );
	display.text( 128, 10, 1000000L / loop_duration, Display::RIGHT );
	display.text( 128, 20, loop_duration, Display::RIGHT );

	atan2( imu.a.y, imu.a.x );

	int radar_size = 30;

	v3<uint16_t> radar;

	radar.x = map( imu.a.x,  0, 1024, 0, radar_size );
	radar.y = map( imu.a.y,  0, 1024, 0, radar_size );
	radar.z = map( imu.a.z,  0, 1024, 0, radar_size );

	display.line( radar_size/2, radar_size/2, radar.x, radar.y );
	display.line( radar_size/2, radar_size,   radar.x, radar_size/2 + radar.z );
}

void loop(void) {
	imu.update();
	pwm.set_angle( 0, loop_number % 181 );
	display.loop( draw );

	loop_number ++;
	loop_start = loop_end;
	loop_end = millis();
	loop_duration = loop_end - loop_start;
}




