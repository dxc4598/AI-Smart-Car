#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include "common.h"
#include "test.hpp"
#include "\libs\timer\timer.hpp"

using namespace std;

TEST test;
Timer SchedulerTimer;

/*CMD parse*/
int comParse(int argc, char **argv)
{
    if((argc > 1) || (argv[0][0] != '-')){
        cout << "Invalid command line argument." << endl;
        return -1;
    }else{
        swtich(argv[0][1]){
            case 'a' :
                cout << "Start PCA9685 & I2C test." << endl;
                test.PCA9685_testInit();
                break;
            case 'b' :
                cout << "Start Buzzer test." << endl;
                test.Buzzer_testInit();
                break;
            case 'c' :
                cout << "Start Motor test." << endl;
                test.Motor_testInit();
                break;
            case 'd' :
                cout << "Start Servo test." << endl;
                test.Servo_testInit();
                break;
            case 'e' :
                cout << "Start Ultrasonic test." << endl;
                test.Ultrasonic_testInit();
            default :
                cout << "Invalid command line argument." << endl;
                return -1;
        }
    }
}

/*Timer Callback*/
void MainLoop(void)
{
    static uint8_t timeSecCnter = 0;

    swtich(argv[0][1]){
        case 'a' :
            if(timeSecCnter == 99)
                test.PCA9685_test();
            break;
        case 'b' :
            if(timeSecCnter == 99)
                test.Buzzer_test();
            break;
        case 'c' :
            if(timeSecCnter == 99)
                test.Motor_test();
            break;
        case 'd' :
            test.Servo_test();
            break;
        case 'e' :
            if(timeSecCnter == 99)
                test.Ultrasonic_test();
            break;
        default :
            break;
    }

    if(timeSecCnter < 99)
        timeSecCnter ++;
    else
        timeSecCnter = 0;
}

/*Main*/
int main(int argc, char **argv)
{
    cout << "Test program running..." << endl;

    /*Get command and execute*/
    comParse(argc, argv);

    /*Create timer*/
    SchedulerTimer.every(10, MainLoop, true);

    /*Create signal*/
    signal(SIGINT, catchSIGINT);

    /*Infinite loop*/
    while(1){
        SchedulerTimer.update();    
    }

    return 0;
}

/*Ctrl + C to exit testing*/
void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed, end program now..." << endl;
        exit(EXIT_SUCCESS);
	}
}




