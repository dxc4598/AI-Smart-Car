// test motor module
# include <cstdlib>
# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Motor.h"
using namespace std;

void test();
void stopTesting();
void catchSIGINT(int);

Motor pwm;


int main() {
	signal(SIGINT, catchSIGINT);
	test();
	
	return 0;
}


void test() {
	cout << "Motor.h Start Testing." << endl;
	
	pwm.setMotorModel(1000, 1000, 1000, 1000);         /* Move Forward. */
	cout << "Moving Forward." << endl;
	sleep(1);
	
	pwm.setMotorModel(-1000, -1000, -1000, -1000);     /* Move Back. */
	cout << "Moving Back." << endl;
	sleep(1);
	
	pwm.setMotorModel(-1500, -1500, 2000, 2000);       /* Turn Left. */
	cout << "Turning Left." << endl;
	sleep(1);
	
	pwm.setMotorModel(2000, 2000, -1500, -1500);       /* Turn Right. */
	cout << "Turning Right." << endl;
	sleep(1);
	
	stopTesting();
}


void stopTesting() {
	cout << "Motor.h Stop Testing." << endl;
	pwm.setMotorModel(0, 0, 0, 0);                     /* Stop */
	
	exit(EXIT_SUCCESS);
}


void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed." << endl;
		stopTesting();
	}
}

