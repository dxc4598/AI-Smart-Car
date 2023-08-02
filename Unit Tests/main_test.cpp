/*
 * This file is the main file for testing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include "common.hpp"
#include "test.hpp"
#include "\libs\timer\timer.hpp"
using namespace std;

TEST test;
Timer SchedulerTimer;

/* CMD Parse */
int comParse(int argc, char **argv)
{
    if ((argc > 1) || (argv[0][0] != '-')) {
        cout << "Invalid Command Line Argument." << endl;
        return -1;
    }
	else {
        switch(argv[0][1]) {
            case 'a' :
                cout << "Start PCA9685 Test." << endl;
                test.PCA9685_testInit();
                break;
            case 'b' :
                cout << "Start Buzzer Test." << endl;
                test.Buzzer_testInit();
                break;
            case 'c' :
                cout << "Start Motor Test." << endl;
                test.Motor_testInit();
                break;
            case 'd' :
                cout << "Start Servo Test." << endl;
                test.Servo_testInit();
                break;
            case 'e' :
                cout << "Start Ultrasonic Test." << endl;
                test.Ultrasonic_testInit();
            default :
                cout << "Invalid Command Line Argument." << endl;
                return -1;
        }
    }
}

/* Timer Callback */
void MainLoop(void)
{
    static uint8_t timeSecCnter = 0;

    switch(argv[0][1]) {
        case 'a' :
            if (timeSecCnter == 99)
                test.PCA9685_test();
            break;
        case 'b' :
            if (timeSecCnter == 99)
                test.Buzzer_test();
            break;
        case 'c' :
            if (timeSecCnter == 99)
                test.Motor_test();
            break;
        case 'd' :
            test.Servo_test();
            break;
        case 'e' :
            if (timeSecCnter == 99)
                test.Ultrasonic_test();
            break;
        default :
            break;
    }

    if (timeSecCnter < 99)
        timeSecCnter ++;
    else
        timeSecCnter = 0;
}

int main(int argc, char **argv)
{
    cout << "Test Program Running..." << endl;

    /* Get Command and Execute */
    comParse(argc, argv);

    /* Create Timer */
    SchedulerTimer.every(10, MainLoop, true);

    /* Get Signal */
    signal(SIGINT, catchSIGINT);

    while(1){
        SchedulerTimer.update();    
    }

    return 0;
}

/*Ctrl + c to Exit */
void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed, End Program Now..." << endl;
        exit(EXIT_SUCCESS);
	}
}

