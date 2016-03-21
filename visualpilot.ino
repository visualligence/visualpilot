#include "./adapters/imu/l3gd20h.h"
#include "./adapters/imu/lsm303_a.h"
#include "./adapters/imu/lsm303_m.h"

uint16_t loop_start = 0;
uint16_t loop_end = 1;
uint16_t loop_duration = 1;

IMU * imu_a, * imu_g, * imu_m;

void setup(void) {
	Serial.begin( 9600 );
	while( !Serial );

// 	imu_g = new L3GD20();
// 	imu_g->setup();

// 	imu_a = new LSM303_A();
// 	imu_a->setup();

	imu_m = new LSM303_M();
	imu_m->setup();

	Wire.begin();
	Wire.setClock( 400000L );
}

void loop(void) {
	Serial.print( " " );

// 	Serial.print( loop_duration );
// 	imu_g->g.print();
// 	imu_a->a.print();
	imu_m->m.print();
// 	imu->m.print();
//
// 	Serial.print( imu->t );

	Serial.println();

// 	imu_g->loop();
	imu_a->loop();
	imu_m->loop();

	loop_start = loop_end;
	loop_end = millis();
	loop_duration = loop_end - loop_start;
}




