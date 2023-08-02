/* 
 * This file defines functions to control the camera of the car.
 */

#include "dev_servo.h"


SERVO::SERVO(void)
{
	pwmServo.setPWMFreq(50);
	pwmServo.setServoPulse(8, 1500);
	pwmServo.setServoPulse(9, 1500);
}

SERVO::~ SERVO(void)
{

}

/* Assign Angle to Control the movement of the Carema */
void SERVO::setServoPWM(uint8_t channel, double angle, int error=10) 
{
	int temp = (int) (angle + error) / 0.09;
	
	switch(channel){
		case 0 : pwmServo.setServoPulse(8, 2500 - temp);		break;
		case 1 : pwmServo.setServoPulse(9, 500 + temp);			break;
		
		defualt :  break;
	}
}

