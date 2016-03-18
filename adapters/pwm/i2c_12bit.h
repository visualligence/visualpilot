#include <Wire.h>

#include <Adafruit_PWMServoDriver.h> // https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

#define MIN_PULSE_US       544
#define MAX_PULSE_US      2400
#define DEFAULT_PULSE_US  1500
#define REFRESH_SERVO_US 20000
#define PWM_RANGE         4096

#define MIN_SERVO 112  // ( MIN_PULSE_US * PWM_RANGE ) / REFRESH_SERVO_US + 1;
#define MAX_SERVO 493  // ( MAX_PULSE_US * PWM_RANGE ) / REFRESH_SERVO_US - 1;

#define US_IN_S 1000000
#define ADAFRUIT_FREQUENCY  ( US_IN_S / ( 0.9 * REFRESH_SERVO_US ) )

class PWM : private Adafruit_PWMServoDriver
{

public:

	PWM()
	: Adafruit_PWMServoDriver()
	{
	}

	void setup( void )
	{
		reset();
		setPWMFreq( ADAFRUIT_FREQUENCY );

		// save I2C bitrate
		//uint8_t twbrbackup = TWBR;
		// must be changed after calling Wire.begin() (inside pwm.begin())
		//TWBR = 12; // upgrade to 400KHz!
	}

	void set( uint8_t pin, uint16_t value )
	{
		setPWM( pin, 0, value );
	}

	void set_angle( uint8_t pin, uint8_t angle )
	{
		set( pin, map( angle, 0, 180, MIN_SERVO, MAX_SERVO ) );
	}
};

