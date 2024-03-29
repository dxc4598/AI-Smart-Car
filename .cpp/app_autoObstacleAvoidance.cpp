/* 
 * This file defines functions to control the indoor behavior of the car.
 */

#include "app_autoObstacleAvoidance.hpp"
# include <sys/time.h>
using namespace std;


APP_AUTO_OBSTACLE_AVOIDANCE::APP_AUTO_OBSTACLE_AVOIDANCE(void)
{
	Buzzer = new BUZZER;
    Motor = new MOTOR;
    Servo = new SERVO;
    Ultrasonic = new ULTRASONIC;
}

APP_AUTO_OBSTACLE_AVOIDANCE::~ APP_AUTO_OBSTACLE_AVOIDANCE(void)
{
	delete Buzzer;
	delete Motor;
	delete Servo;
	delete Ultrasonic;
}

/* Initialize */
void APP_AUTO_OBSTACLE_AVOIDANCE::setUp(void)
{
	int L, M, R;
	
    for (int i = 30; i < 151; i += 60) {
        Servo -> setServoPWM(0, i);
        usleep(200000);
		
        if (i == 30) {
            L = getDistance();
            cout << "Left Side Distance is " << L << " cm" << endl; 
        }
        else if (i == 90) {
            M = getDistance();
            cout << "Middle Side Distance is " << M << " cm" << endl; 
        }
        else {
            R = getDistance();
            cout << "Right Side Distance is " << R << " cm" << endl; 
        }
    }

	run_step = 0;
}

/* Logics of Indoor Obstacle Avoidance */
void APP_AUTO_OBSTACLE_AVOIDANCE::runMotor(int L, int M, int R)
{
	if (((L < 30) && (M < 30) && (R < 30)) || M < 30 ) {
        Motor -> setMotorModel(-1450, -1450, -1450, -1450);
        usleep(100000);
		
        if (L < R) {
            Motor -> setMotorModel(1450, 1450, -1450, -1450);
        }
        else {
            Motor -> setMotorModel(-1450, -1450, 1450, 1450);
        }
    }
	else if ((L < 30) && (M < 30)) {
        Motor -> setMotorModel(1500, 1500, -1500, -1500);
    }
	else if ((R < 30) && (M < 30)) {
        Motor -> setMotorModel(-1500, -1500, 1500, 1500);
    }
	else if (L < 20) {
        Motor -> setMotorModel(2000, 2000, -500, -500);
		
        if (L < 10) {
            Motor -> setMotorModel(1500, 1500, -1000, -1000);
        }
    }
	else if (R < 20) {
        Motor -> setMotorModel(-500, -500, 2000, 2000);
		
        if (R < 10) {
            Motor -> setMotorModel(-1500, -1500, 1500, 1500);
        }
    }
	else {
        Motor -> setMotorModel(600, 600, 600, 600);
    }
}

/* Usage of runMotor() */
void APP_AUTO_OBSTACLE_AVOIDANCE::run(void)
{
	int L, M, R;

	switch(run_step){
		case 0 :
			Servo -> setServoPWM(0, 90);
			break;
		case 1 :
			M = Ultrasonic -> getDistance();
			runMotor(L, M, R);
			break;
		case 2 :
			Servo -> setServoPWM(0, 30);
			break;
		case 3 :
			L = Ultrasonic -> getDistance();
			runMotor(L, M, R);
			break;
		case 4 :
			Servo -> setServoPWM(0, -30);
			break;
		case 5 :
			R = Ultrasonic -> getDistance();
			runMotor(L, M, R);
			break;
		case 6 :
			Servo -> setServoPWM(0, 30);
			break;
		case 7 :
			L = Ultrasonic -> getDistance();
			runMotor(L, M, R);
			break;
		case 8 :
			Servo -> setServoPWM(0, 90);
			break;
		case 9 :
			M = Ultrasonic -> getDistance();
			runMotor(L, M, R);
		case 10 :
			Servo -> setServoPWM(0, 150);
			break;
		case 11 :
			R = Ultrasonic -> getDistance();
			runMotor(L, M, R);
		default :
			break;
	}

	if(run_step < 11)
		run_step ++;
	else
		run_step = 0;
}

