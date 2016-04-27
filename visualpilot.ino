#include "./adapters/imu/adxl345.h"
#include "./adapters/imu/l3gd20.h"
#include "./adapters/imu/hmc5883l.h"
#include "./adapters/imu/bmp180.h"
#include "./adapters/imu/hcsr04.h"

#include "./adapters/rc/rc.h"

#include "./scheduler/scheduler.h"

ADXL345 * a;
L3GD20 * g;
HMC5883L * m;
BMP180 * b;
HCSR04 * h;

Scheduler * s;

RCChannel * in_t, * in_x, * in_y, * in_z;

void setup(void) {
	Serial.begin( 9600 );
	while( !Serial );

	h = new HCSR04Pins<D0,D1>();

// 	in_t = new RCChannelPin<D5>();
// 	in_x = new RCChannelPin<D6>();
// 	in_y = new RCChannelPin<D7>();
// 	in_z = new RCChannelPin<D8>();
//
// 	Wire.begin();
// 	Wire.setClock( 400000L );
//
// 	I2CDevice::scan();
//
// 	a = new ADXL345();
// 	g = new L3GD20();
// 	m = new HMC5883L();
// 	b = new BMP180();
// 	s = new Scheduler();
}

void loop(void) {
// 	s->loop();
// 	a->loop();
// 	g->loop();
// 	m->loop();
// 	b->loop();
	h->loop();

// 	s->print();
// 	a->print();
// 	g->print();
// 	m->print();
// 	b->print();
// 	h->print();

// 	in_t->print();
// 	in_x->print();
// 	in_y->print();
// 	in_z->print();

// 	Serial.println();
//  	delay( 25 );
}




