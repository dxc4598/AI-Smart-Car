# pragma once

# include <string>
# include "PCA9685.h"
using namespace std;


class Servo {
	public: 
		Servo();
		void setServoPWM(string, double, int);
		
	private: 
		PCA9685 pwmServo;
};


Servo::Servo(void) {
	pwmServo.setPWMFreq(50);
	pwmServo.setServoPulse(8, 1500);
	pwmServo.setServoPulse(9, 1500);
}


void Servo::setServoPWM(string channel, double angle, int error=10) {
	int temp = (int) (angle + error) / 0.09;
	
	if (channel == "0") {
		pwmServo.setServoPulse(8, 2500 - temp);
	}
	else if (channel == "1") {
		pwmServo.setServoPulse(9, 500 + temp);
	}
	else if (channel == "2") {
		pwmServo.setServoPulse(10, 500 + temp);
	}
	else if (channel == "3") {
		pwmServo.setServoPulse(11, 500 + temp);
	}
	else if (channel == "4") {
		pwmServo.setServoPulse(12, 500 + temp);
	}
	else if (channel == "5") {
		pwmServo.setServoPulse(13, 500 + temp);
	}
	else if (channel == "6") {
		pwmServo.setServoPulse(14, 500 + temp);
	}
	else if (channel == "7") {
		pwmServo.setServoPulse(15, 500 + temp);
	}
}
