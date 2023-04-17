# include <string>
# include <fstream>
# include <iostream>
# include <unistd.h>
# include "Motor.h"
using namespace std;


Motor pwm;
int main() {
	ifstream f ("direction.txt");
	string s;
	
	if (f.is_open()) {
		while (!f.eof()) {
			f >> s;
			cout << s << endl;
			
			if (s == "stop") {
				pwm.setMotorModel(0, 0, 0, 0);
			}
			else if (s == "go-straight") {
				f >> s;
				
				int sleep_time = (int) stoi(s) * 1612903;
				cout << sleep_time << endl;
				pwm.setMotorModel(1200, 1200, 1200, 1200);
				usleep(sleep_time);
				
			}
			else if (s == "turn-left") {
				f >> s;
				cout << s << endl;
				int sleep_time = (int) stoi(s) * 1612903;
				pwm.setMotorModel(-1500, -1500, 2000, 2000);
				sleep(1);
				pwm.setMotorModel(0, 0, 0, 0);
				sleep(1);
				pwm.setMotorModel(1200, 1200, 1200, 1200);
				usleep(sleep_time);
			}
			else if (s == "turn-right") {
				f >> s;
				
				int sleep_time = (int) stoi(s) * 1612903;
				pwm.setMotorModel(2000, 2000, -1500, -1500);
				sleep(1);
				pwm.setMotorModel(0, 0, 0, 0);
				sleep(1);
				pwm.setMotorModel(1200, 1200, 1200, 1200);
				usleep(sleep_time);
			}
 			pwm.setMotorModel(0, 0, 0, 0);
 			sleep(1);
 		}
	}
		
	
/*	pwm.setMotorModel(1200, 1200, 1200, 1200);
	sleep(3);
	pwm.setMotorModel(0, 0, 0, 0);
	
*/	return 0;
	}
