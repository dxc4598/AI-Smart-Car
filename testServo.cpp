# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Servo.h"
using namespace std;

void test();
void stopTesting();
void catchSIGINT(int);

Servo pwm;
bool stop = false;


int main() {
	signal(SIGINT, catchSIGINT);
	cout << "Servo.h Start Testing." << endl;
	
	while (true) {
		test();
		
		if (stop) {
			stopTesting();
			break;
		}
	}
	
	return 0;
}


void test() {
	for (int i = 50; i < 110; i++) {
		pwm.setServoPWM("0", i);
		usleep(10000);
	}
	for (int i = 110; i > 50; i--) {
		pwm.setServoPWM("0", i);
		usleep(10000);
	}
	for (int i = 80; i < 150; i++) {
		pwm.setServoPWM("1", i);
		usleep(10000);
	}
	for (int i = 150; i > 80; i--) {
		pwm.setServoPWM("1", i);
		usleep(10000);
	}
}


void stopTesting() {
	pwm.setServoPWM("0", 90);
	pwm.setServoPWM("1", 90);
	cout << "Servo.h Stop Testing." << endl;
}


void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c has been pressed." << endl;
		stop = true;
	}
}
            
