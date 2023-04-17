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

  pwm.setMotorModel(600, 600, 600, 600); 
  sleep(1);

  pwm.setMotorModel(2000, 2000, -500, -500);
  usleep(700000);
  pwm.setMotorModel(-500, -500, 2000, 2000);
  usleep(700000);
  
  pwm.setMotorModel(0, 0, 0, 0);
  sleep(2);
  
  pwm.setMotorModel(600, 600, 600, 600); 
  sleep(1);

  pwm.setMotorModel(-500, -500, 2000, 2000);
  sleep(700000);
  pwm.setMotorModel(2000, 2000, -500, -500);
  sleep(700000);
  
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

