# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Motor.h"
# include "Servo.h"
# include "Ultrasonic.h"
using namespace std;

void testRun();
void testGetDistance();
void stopTesting();
void catchSIGINT(int);

Motor pwm;
Servo pwmServo;
Ultrasonic ultrasonic;
bool stop = false;


int main() {
	int number = 0;
	
	signal(SIGINT, catchSIGINT);
/*	cout << "Please select the test." << endl;;
	number = cin >> "1 for testGetDistance() and 2 for testRun().";
	
	while (true) {
		testGetDistance();
		
		if (stop) {
			stopTesting();
			break;
		}
	}
*/
	ultrasonic.setUp();
	while (true) {
		testRun();
		
		if (stop) {
			stopTesting();
			break;
		}
	}
	
	return 0;
}


void testRun() {
	ultrasonic.run();
}


void testGetDistance() {
	int data;
	data = ultrasonic.getDistance();
	cout << "Obstacle Distance is " << data << " cm" << endl;
	sleep(1);
}


void stopTesting() {
	pwm.setMotorModel(0, 0, 0, 0);
	pwmServo.setServoPWM("0", 90);
	cout << "Ultrasonic.h Stop Testing." << endl;
}


void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c has been pressed." << endl;
		stop = true;
	}
}
    
