#include "./adapters/imu/adxl345.h"
#include "./adapters/imu/l3gd20.h"
#include "./adapters/imu/hmc5883l.h"
#include "./adapters/imu/bmp180.h"

uint16_t loop_start = 0;
uint16_t loop_end = 1;
uint16_t loop_duration = 1;

ADXL345 * a;
L3GD20 * g;
HMC5883L * m;
BMP180 * b;

void setup(void) {
	Serial.begin( 9600 );
	while( !Serial );

	Wire.begin();
	Wire.setClock( 400000L );

	I2CDevice::scan();

	a = new ADXL345();
	g = new L3GD20();
	m = new HMC5883L();
	b = new BMP180();
}

void loop(void) {
	a->loop();
	g->loop();
	m->loop();
	b->loop();

	a->print();
	g->print();
	m->print();
	b->print();

	Serial.println();

	loop_start = loop_end;
	loop_end = millis();
	loop_duration = loop_end - loop_start;
}




