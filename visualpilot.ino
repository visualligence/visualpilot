#include "./adapters/imu/adxl345.h"
#include "./adapters/imu/l3gd20.h"
#include "./adapters/imu/hmc5883l.h"
#include "./adapters/imu/bmp180.h"

#include "./scheduler/scheduler.h"

ADXL345 * a;
L3GD20 * g;
HMC5883L * m;
BMP180 * b;
Scheduler * s;

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
	s = new Scheduler();
}

void loop(void) {
	a->loop();
	g->loop();
	m->loop();
	b->loop();
	s->loop();

	a->print();
	g->print();
	m->print();
	b->print();
	s->print();

	Serial.println();
}




