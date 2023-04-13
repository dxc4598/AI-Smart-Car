# pragma once

# include <string>
# include <iostream>
# include <wiringPi.h>
using namespace std;

# define Buzzer_Pin 17


class Buzzer {
	public: 
		Buzzer();
		void makeSound(string);
};


Buzzer::Buzzer(void) {
	wiringPiSetupGpio();
    pinMode(Buzzer_Pin, OUTPUT);
}


void Buzzer::makeSound(string command) {
	if (command == "0") {
		digitalWrite(Buzzer_Pin, LOW);
	}
	else if (command == "1") {
		digitalWrite(Buzzer_Pin, HIGH);
	}
	else {
		cout << "Invalid Command." << endl;
	}
}

