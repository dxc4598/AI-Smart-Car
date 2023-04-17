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


int main() {
	signal(SIGINT, catchSIGINT);

	ultrasonic.setUp();
	while (true) {
		testRun();
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
	cout << "Ultrasonic.h Stop Testing." << endl;
	pwm.setMotorModel(0, 0, 0, 0);
	pwmServo.setServoPWM("0", 90);
	
	exit(EXIT_SUCCESS);
}


void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed." << endl;
		stopTesting();
	}
}
    
