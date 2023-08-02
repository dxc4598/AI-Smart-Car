/* 
 * This file defines functions to control the outdoor behavior of the car.
 */

#include "app_autoRun_map.hpp"
# include <sys/time.h>
using namespace std;

#define Servo_Min               10
#define Servo_Max               90
#define Min_Distance            20
#define Max_Distance            40


APP_AUTORUN_MAP::APP_AUTORUN_MAP(void)
{
	Buzzer = new BUZZER;
    Motor = new MOTOR;
    Servo = new SERVO;
    Ultrasonic = new ULTRASONIC;

	BuzzerOn = 0;
	MotorCtrlCmd = CMD_INVALID;
	MotorCtrlState = ST_STOP;
	MotorCtrlTimeCnt = 0;
	MotorCtrlGoStraightTime = 0;
	L = 0;
	M = 0;
	R = 0;
}

APP_AUTORUN_MAP::~ APP_AUTORUN_MAP(void)
{
	delete Buzzer;
	delete Motor;
	delete Servo;
	delete Ultrasonic;
}

void APP_AUTORUN_MAP::BuzzerAlert(uint32_t buzzer_on_time_ms)
{
	BuzzerOn = buzzer_on_time_ms;
}

/* Manage Buzzer */
void APP_AUTORUN_MAP::BuzzerMng(void)
{
	if (BuzzerOn > 0) {
		BuzzerOn --;
		Buzzer -> control(1);
	}
	else {
		Buzzer -> control(0);
	}
}

void APP_AUTORUN_MAP::MotorCtrl(MOTOR_CTRL_CMD cmd)
{
	MotorCtrlCmd = cmd;
}

/* Check Motor State */
uint8_t APP_AUTORUN_MAP::MotorCtrlCheckCmdBusy(void)
{
	if ((MotorCtrlCmd != CMD_INVALID) || (MotorCtrlGoStraightTime > 0))
		return 0x55;
	else
		return 0x00;
}

void APP_AUTORUN_MAP::MotorCtrlSetGoStraightTime(uint32_t time)
{
	MotorCtrlGoStraightTime = time;
}

/* Get Motor State */
void APP_AUTORUN_MAP::MotorCtrlGetState(void)
{
	switch (MotorCtrlState) {
		case ST_STOP :
			switch (MotorCtrlCmd){
				case CMD_GO_STRAIGHT :	MotorCtrlState = ST_GO_STRAIGHT;	MotorCtrlCmd = CMD_INVALID; break;
				default: 				MotorCtrlState = ST_STOP;			MotorCtrlCmd = CMD_INVALID; break;
			}
			break;
		case ST_GO_STRAIGHT :
			switch (MotorCtrlCmd){
				case CMD_STOP : 		MotorCtrlState = ST_STOP;			MotorCtrlCmd = CMD_INVALID; break;
				case CMD_TRUN_LEFT :	MotorCtrlState = ST_TURN_LEFT;		MotorCtrlCmd = CMD_INVALID; break;
				case CMD_TRUN_RIGHT :	MotorCtrlState = ST_TURN_RIGHT;		MotorCtrlCmd = CMD_INVALID; break;
				case CMD_GO_STRAIGHT :	MotorCtrlState = ST_GO_STRAIGHT;	MotorCtrlCmd = CMD_INVALID; break;
				default: 
					if (M < Min_Distance)
						MotorCtrlState = ST_STOP;
					else if (L < Min_Distance)
						MotorCtrlState = ST_AVOID_LEFT_OBSTACLE_1;
					else if (L > Max_Distance)
						MotorCtrlState = ST_AVOID_RIGHT_OBSTACLE_1;
					else {
						if (MotorCtrlGoStraightTime > 0) {
							MotorCtrlGoStraightTime --;
							MotorCtrlState = ST_GO_STRAIGHT;
						}
						else
							MotorCtrlState = ST_STOP;
					}
					
					MotorCtrlCmd = CMD_INVALID;
					break;
			}

			MotorCtrlTimeCnt = 0;
			break;
		case ST_AVOID_LEFT_OBSTACLE_1 :
			if (MotorCtrlTimeCnt < 700)
				MotorCtrlTimeCnt ++;
			else {
				MotorCtrlTimeCnt = 0;
				MotorCtrlState = ST_AVOID_LEFT_OBSTACLE_2;
			}
			break;
		case ST_AVOID_LEFT_OBSTACLE_2 :
			if (MotorCtrlTimeCnt < 700)
				MotorCtrlTimeCnt ++;
			else {
				MotorCtrlTimeCnt = 0;
				MotorCtrlState = ST_GO_STRAIGHT;
			}
			break;
		case ST_AVOID_LEFT_OBSTACLE_3 :
			MotorCtrlState = ST_GO_STRAIGHT;
			break;
		case ST_AVOID_RIGHT_OBSTACLE_1 :
			if (MotorCtrlTimeCnt < 700)
				MotorCtrlTimeCnt ++;
			else {
				MotorCtrlTimeCnt = 0;
				MotorCtrlState = ST_AVOID_RIGHT_OBSTACLE_2;
			}
			break;
		case ST_AVOID_RIGHT_OBSTACLE_2 :
			if (MotorCtrlTimeCnt < 700)
				MotorCtrlTimeCnt ++;
			else {
				MotorCtrlTimeCnt = 0;
				MotorCtrlState = ST_GO_STRAIGHT;
			}
			break;
		case ST_AVOID_RIGHT_OBSTACLE_3 :
			MotorCtrlState = ST_GO_STRAIGHT;
			break;
		case ST_TURN_LEFT :
			if (MotorCtrlTimeCnt < 1000)
				MotorCtrlTimeCnt ++;
			else {
				MotorCtrlTimeCnt = 0;
				MotorCtrlState = ST_GO_STRAIGHT;
			}
			break;
		case ST_TURN_RIGHT :
			if (MotorCtrlTimeCnt < 1000)
				MotorCtrlTimeCnt ++;
			else {
				MotorCtrlTimeCnt = 0;
				MotorCtrlState = ST_GO_STRAIGHT;
			}
			break;
		default:
			break;
	}
}

/* Control Motor */
void APP_AUTORUN_MAP::MotorCtrlMng(void)
{
	MotorCtrlGetState();

	switch (MotorCtrlState){
		case ST_STOP :
			Motor -> setMotorModel(0, 0, 0, 0);
			break;
		case ST_GO_STRAIGHT :
			Motor -> setMotorModel(600, 600, 600, 600);
			break;
		case ST_AVOID_LEFT_OBSTACLE_1 :
			Motor -> setMotorModel(2000, 2000, -500, -500);
			break;
		case ST_AVOID_LEFT_OBSTACLE_2 :
			Motor -> setMotorModel(-500, -500, 2000, 2000);
			break;
		case ST_AVOID_LEFT_OBSTACLE_3 :
			Motor -> setMotorModel(0, 0, 0, 0);
			break;
		case ST_AVOID_RIGHT_OBSTACLE_1 :
			Motor -> setMotorModel(-500, -500, 2000, 2000);
			break;
		case ST_AVOID_RIGHT_OBSTACLE_2 :
			Motor -> setMotorModel(2000, 2000, -500, -500);
			break;
		case ST_AVOID_RIGHT_OBSTACLE_3 :
			Motor -> setMotorModel(0, 0, 0, 0);
			break;
		case ST_TURN_LEFT :
			Motor -> setMotorModel(-1500, -1500, 2000, 2000);
			break;
		case ST_TURN_RIGHT :
			Motor -> setMotorModel(2000, 2000, -1500, -1500);
			break;
		default:
			break;
	}
}

/* Refresh for Getting Distance */
void APP_AUTORUN_MAP::RefreshDistance(void)
{
	static uint32_t step = 0;

	switch (step){
		case 0 :
			Servo -> setServoPWM(0, 30);
			L = Ultrasonic -> getDistance();
			break;
		case 200 :
			Servo -> setServoPWM(0, 90);
			M = Ultrasonic -> getDistance();
			break;
		case 400 :
			Servo -> setServoPWM(0, 150);
			R = Ultrasonic -> getDistance();
			break;
		default :
			break;
	}

	if (step < 600)
		step ++;
	else
		step = 0;
}

