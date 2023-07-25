/******************************************************************************************************************
 * The purpose of this function is to drive the servo motor of the car
*****************************************************************************************************************/
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

void SERVO::setServoPWM(string channel, double angle, int error=10) 
{
	int temp = (int) (angle + error) / 0.09;
	
	switch(channel){
		case "0" : pwmServo.setServoPulse(8, 2500 - temp);		break;
		case "1" : pwmServo.setServoPulse(9, 500 + temp);		break;
		case "2" : pwmServo.setServoPulse(10, 500 + temp);		break;
		case "3" : pwmServo.setServoPulse(11, 500 + temp);		break;
		case "4" : pwmServo.setServoPulse(12, 500 + temp);		break;
		case "5" : pwmServo.setServoPulse(13, 500 + temp);		break;
		case "6" : pwmServo.setServoPulse(14, 500 + temp);		break;
		case "7" : pwmServo.setServoPulse(15, 500 + temp);		break;
		defualt :  break;
	}
}

