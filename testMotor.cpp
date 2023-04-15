# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Motor.h"
using namespace std;

void test();
void stopTesting();
void catchSIGINT(int);

Motor pwm;
bool stop = false;


int main() {
	signal(SIGINT, catchSIGINT);
	test();
		
	if (stop) {
		stopTesting();
		exit(EXIT_SUCCESS);
	}
	
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
	pwm.setMotorModel(0, 0, 0, 0);                     /* Stop */
	cout << "Motor.h Stop Testing." << endl;
}


void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c has been pressed." << endl;
		stop = true;
	}
}

