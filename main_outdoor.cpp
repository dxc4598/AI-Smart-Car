/*
 * This file is the main file for the car to run outdoor.
 */

#include "common.hpp"
#include "app_autoRun_map.hpp"
#include "app_map.hpp"
#include "libs/timer/timer.hpp"
using namespace std;


APP_AUTORUN_MAP Autorun;
APP_MAP Map;
uint8_t StopProgram;
TIMER SchedulerTimer;
uint32_t Setup;

void catchSIGINT(int signal);


void autoRunLoop(void)
{
    Autorun.BuzzerMng();
    Autorun.RefreshDistance();
    Autorun.MotorCtrlMng();

    if (Setup < 2000)
        Setup ++;
}

int main(int argc, char **argv)
{
    int motor_go_straight_time;
    string instruction;
    
    StopProgram = 0;
    Setup = 0;

    cout << "Outdoor Program with Google Map Started." << endl;

    /* Create Timer */
    SchedulerTimer.create(1, autoRunLoop, true);

    /* Get Directions */
    Map.getDirection();

    /* Get signal*/
    signal(SIGINT, catchSIGINT);

    ifstream file ("direction.txt");

    /* Follow the Map Directions */
    if (file.is_open()) {
		while (! file.eof()) {
            if ((Setup >= 2000) && (! Autorun.MotorCtrlCheckCmdBusy())) {
                file >> instruction;
                
                if (instruction == "stop") {
                    Autorun.BuzzerAlert(250);
                    Autorun.MotorCtrl(CMD_STOP);
                    break;
                }
				else if (instruction == "go-straight") {
                    file >> instruction;
                    motor_go_straight_time = (int) stoi(instruction) * 1612903 / 1000;

                    Autorun.BuzzerAlert(250);
                    Autorun.MotorCtrl(CMD_GO_STRAIGHT);
                    Autorun.MotorCtrlSetGoStraightTime(motor_go_straight_time);
                }
				else if (instruction == "turn-left") {
                    file >> instruction;
                    motor_go_straight_time = (int) stoi(instruction) * 1612903 / 1000;

                    Autorun.BuzzerAlert(250);
                    Autorun.MotorCtrl(CMD_TRUN_LEFT);
                    Autorun.MotorCtrlSetGoStraightTime(motor_go_straight_time);
				}
				else if (instruction == "turn-right") {
                    file >> instruction;
                    motor_go_straight_time = (int) stoi(instruction) * 1612903 / 1000;

                    Autorun.BuzzerAlert(250);
                    Autorun.MotorCtrl(CMD_TRUN_RIGHT);
                    Autorun.MotorCtrlSetGoStraightTime(motor_go_straight_time);
                }
            }

            SchedulerTimer.update();

            if (StopProgram) {
                StopProgram = 0;
                Autorun.MotorCtrl(CMD_STOP);
                
                while (Autorun.MotorCtrlCheckCmdBusy());
                break;
            }
 		}
	}

    return 0;
}

/*Ctrl + c to Exit */
void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed, End Program Now..." << endl;
		
        StopProgram = 0x55;
        exit(EXIT_SUCCESS);
	}
}

