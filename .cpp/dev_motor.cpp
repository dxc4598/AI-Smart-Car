/* 
 * This file defines functions to control the wheels of the car.
 */
 
#include "dev_motor.hpp"


MOTOR::MOTOR(void)
{
	pwm.setPWMFreq(50);
}

MOTOR::~ MOTOR(void)
{

}

/* Control the Range of Duties */
void Motor::setDutyRange(int duty1, int duty2, int duty3, int duty4) 
{
	if (duty1 > 4095) {
		duty1 = 4095;
	} 
	else if (duty1 < -4095) {
		duty1 = -4095;
	}
	
	if (duty2 > 4095) {
		duty2 = 4095;
	} 
	else if (duty2 < -4095) {
		duty2 = -4095;
	}
	
	if (duty3 > 4095) {
		duty3 = 4095;
	} 
	else if (duty3 < -4095) {
		duty3 = -4095;
	}
	
	if (duty4 > 4095) {
		duty4 = 4095;
	} 
	else if (duty4 < -4095) {
		duty4 = -4095;
	}
}

/* Assign Duty to the Left Upper Wheel */
void Motor::setLeftUpperWheel(int duty) 
{
	if (duty > 0) {
		pwm.setMotorPWM(0, 0);
		pwm.setMotorPWM(1, duty);
	}
	else if (duty < 0) {
		pwm.setMotorPWM(1, 0);
		pwm.setMotorPWM(0, abs(duty));
	}
	else {
		pwm.setMotorPWM(0, 4095);
        pwm.setMotorPWM(1, 4095);
	}
}

/* Assign Duty to the Left Lower Wheel */
void Motor::setLeftLowerWheel(int duty) 
{
	if (duty > 0) {
		pwm.setMotorPWM(3, 0);
		pwm.setMotorPWM(2, duty);
	}
	else if (duty < 0) {
		pwm.setMotorPWM(2, 0);
		pwm.setMotorPWM(3, abs(duty));
	}
	else {
		pwm.setMotorPWM(2, 4095);
        pwm.setMotorPWM(3, 4095);
	}
}

/* Assign Duty to the Right Upper Wheel */
void Motor::setRightUpperWheel(int duty) 
{
	if (duty > 0) {
		pwm.setMotorPWM(6, 0);
		pwm.setMotorPWM(7, duty);
	}
	else if (duty < 0) {
		pwm.setMotorPWM(7, 0);
		pwm.setMotorPWM(6, abs(duty));
	}
	else {
		pwm.setMotorPWM(6, 4095);
        pwm.setMotorPWM(7, 4095);
	}
}

/* Assign Duty to the Right Lower Wheel */
void Motor::setRightLowerWheel(int duty) 
{
	if (duty > 0) {
		pwm.setMotorPWM(4, 0);
		pwm.setMotorPWM(5, duty);
	}
	else if (duty < 0) {
		pwm.setMotorPWM(5, 0);
		pwm.setMotorPWM(4, abs(duty));
	}
	else {
		pwm.setMotorPWM(4, 4095);
        pwm.setMotorPWM(5, 4095);
	}
}

/* Assign Duties to the 4 Wheels */
void Motor::setMotorModel(int duty1, int duty2, int duty3, int duty4) 
{
	setDutyRange(duty1, duty2, duty3, duty4);
	
    setLeftUpperWheel(-duty1);
    setLeftLowerWheel(-duty2);
    setRightUpperWheel(-duty3);
    setRightLowerWheel(-duty4);
}

