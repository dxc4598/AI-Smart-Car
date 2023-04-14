# pragma once

# include <cstdlib>
# include "PCA9685.h"
using namespace std;


class Motor {
	public:
    	Motor();
		void setMotorModel(int, int, int, int);
		
	private: 
		PCA9685 pwm;
		
		void setDutyRange(int, int, int, int);
		void setLeftUpperWheel(int);
		void setLeftLowerWheel(int);
		void setRightUpperWheel(int);
		void setRightLowerWheel(int);
};


Motor::Motor(void) {
    pwm.setPWMFreq(50);
}


void Motor::setDutyRange(int duty1, int duty2, int duty3, int duty4) {
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


void Motor::setLeftUpperWheel(int duty) {
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


void Motor::setLeftLowerWheel(int duty) {
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


void Motor::setRightUpperWheel(int duty) {
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


void Motor::setRightLowerWheel(int duty) {
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


void Motor::setMotorModel(int duty1, int duty2, int duty3, int duty4) {
	setDutyRange(duty1, duty2, duty3, duty4);
	
    setLeftUpperWheel(-duty1);
    setLeftLowerWheel(-duty2);
    setRightUpperWheel(-duty3);
    setRightLowerWheel(-duty4);
}

