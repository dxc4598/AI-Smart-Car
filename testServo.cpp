# include <cstdlib>
# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Servo.h"
using namespace std;

void test();
void stopTesting();
void catchSIGINT(int);

Servo pwm;


int main() {
	signal(SIGINT, catchSIGINT);
	cout << "Servo.h Start Testing." << endl;
	
	while (true) {
		test();
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
	cout << "Servo.h Stop Testing." << endl;
	pwm.setServoPWM("0", 90);
	pwm.setServoPWM("1", 90);
	
	exit(EXIT_SUCCESS);
}


void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed." << endl;
		stopTesting();
	}
}

