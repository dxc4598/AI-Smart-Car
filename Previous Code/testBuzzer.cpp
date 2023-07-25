// test the buzzer module
# include <cstdlib>
# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Buzzer.h"
using namespace std;

void test();
void stopTesting();
void catchSIGINT(int);

Buzzer buzzer;


int main() {
	signal(SIGINT, catchSIGINT);
	test();
	
	return 0;
}


void test() {
	cout << "Buzzer.h Start Testing." << endl;
	
	buzzer.makeSound("1");
	for (int i = 0; i < 3; i++) {
		sleep(1);
		cout << i+1 << "second(s) passed." << endl;
	}
	
	stopTesting();
}


void stopTesting() {
	cout << "Servo.h Stop Testing." << endl;
	buzzer.makeSound("0");
	
	exit(EXIT_SUCCESS);
}


void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed." << endl;
		stopTesting();
	}
}

