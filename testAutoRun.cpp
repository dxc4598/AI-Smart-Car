// read route from directions.txt, calcute the running time and execute
# include <string>
# include <fstream>
# include <cstdlib>
# include <signal.h>
# include <iostream>
# include <unistd.h>
# include "AutoRun.h"
using namespace std;

void test();
void stopTesting();
void catchSIGINT(int);

AutoRun autoRun;
bool stop = false;


int main() {
	string instruction;
	
	signal(SIGINT, catchSIGINT);
	ifstream file ("direction.txt");
	autoRun.setUp();
	
	if (file.is_open()) {
		while (!file.eof()) {
			file >> instruction;
			
			if (instruction == "stop") {
				autoRun.stop();
				break;
			}
			else if (instruction == "go-straight") {
				file >> instruction;
				
				int sleep_time = (int) stoi(instruction) * 1612903;
				autoRun.goStraight(sleep_time);
				
			}
			else if (instruction == "turn-left") {
				file >> instruction;

				int sleep_time = (int) stoi(instruction) * 1612903;
				autoRun.turnLeft();
				autoRun.goStraight(sleep_time);
			}
			else if (instruction == "turn-right") {
				file >> instruction;
				
				int sleep_time = (int) stoi(instruction) * 1612903;
				autoRun.turnRight();
				autoRun.goStraight(sleep_time);
			}
			else if (stop) {
				stopTesting();
				break;
			}
 		}
	}
	
	return 0;
}


void stopTesting() {
	cout << "AutoRun.h Stop Testing." << endl;
	autoRun.stop();
	
	exit(EXIT_SUCCESS);
}

// if Ctrl + c has been pressed
void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed." << endl;
		stopTesting();
	}
}

