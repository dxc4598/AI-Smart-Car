#ifndef _APP_AUTORUN_MAP_HPP_
#define _APP_AUTORUN_MAP_HPP_

#include "common.hpp"
#include "dev_buzzer.hpp"
#include "dev_motor.hpp"
#include "dev_pca9685.hpp"
#include "dev_servo.hpp"
#include "dev_ultrasonic.hpp"

/*Motor Control*/
typedef enum _tagMOTOR_CTRL_CMD
{
    CMD_INVALID                     = 0x00,
    CMD_STOP                        = 0x11,
    CMD_TRUN_LEFT                   = 0x22,
    CMD_TRUN_RIGHT                  = 0x33,
    CMD_GO_STRAIGHT                 = 0x44
}MOTOR_CTRL_CMD;

/*Motor Run State*/
typedef enum _tagMOTOR_RUN_STATE
{
    ST_STOP                         = 0x00,
    ST_GO_STRAIGHT                  = 0x11,
    ST_AVOID_LEFT_OBSTACLE_1        = 0x22,
    ST_AVOID_LEFT_OBSTACLE_2        = 0x33,
    ST_AVOID_LEFT_OBSTACLE_3        = 0x44,
    ST_AVOID_RIGHT_OBSTACLE_1       = 0x55,
    ST_AVOID_RIGHT_OBSTACLE_2       = 0x66,
    ST_AVOID_RIGHT_OBSTACLE_3       = 0x77, 
    ST_TURN_LEFT                    = 0x88,
    ST_TURN_RIGHT                   = 0x99
}MOTOR_RUN_STATE;


class APP_AUTORUN_MAP {
    public :
        APP_AUTORUN_MAP();
        ~APP_AUTORUN_MAP();

        void BuzzerAlert(uint32_t);
        void BuzzerMng();
        void MotorCtrl(MOTOR_CTRL_CMD);
        uint8_t MotorCtrlCheckCmdBusy();
        void MotorCtrlSetGoStraightTime(uint32_t);
        void MotorCtrlMng();
        void RefreshDistance();
    private:
        BUZZER *Buzzer;
        MOTOR *Motor;
        SERVO *Servo;
        ULTRASONIC *Ultrasonic;

        uint16_t BuzzerOn;
        MOTOR_CTRL_CMD MotorCtrlCmd;
        MOTOR_RUN_STATE MotorCtrlState;
        uint32_t MotorCtrlGoStraightTime;
        uint32_t MotorCtrlTimeCnt;
        int L, M, R;

        void MotorCtrlGetState();
};

#endif
