# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Buzzer.h"
using namespace std;

void test();
void stopTesting();
void catchSIGINT(int);

Buzzer buzzer;
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
	cout << "Buzzer.h Start Testing." << endl;
	
	buzzer.makeSound("1");
	for (int i = 0; i < 3; i++) {
		sleep(1);
		cout << i+1 << "second(s) passed." << endl;
	}
	
	stopTesting();
}


void stopTesting() {
	buzzer.makeSound("0");
	cout << "Servo.h Stop Testing." << endl;
}


void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c has been pressed." << endl;
		stop = true;
	}
}
            
