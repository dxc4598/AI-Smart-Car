/* 
 * This file defines functions to control the behavior of the car.
 */

#ifndef _APP_AUTOOBSTACLEAVOIDANCE_HPP_
#define _APP_AUTOOBSTACLEAVOIDANCE_HPP_

#include "common.hpp"
#include "dev_buzzer.hpp"
#include "dev_motor.hpp"
#include "dev_pca9685.hpp"
#include "dev_servo.hpp"
#include "dev_ultrasonic.hpp"


class APP_AUTO_OBSTACLE_AVOIDANCE {
    public :
        APP_AUTO_OBSTACLE_AVOIDANCE();
        ~APP_AUTO_OBSTACLE_AVOIDANCE();

        void setUp();
        void run();
    private:
        BUZZER *Buzzer;
        MOTOR *Motor;
        SERVO *Servo;
        ULTRASONIC *Ultrasonic;

        uint8_t run_step;
        
        void runMotor(int, int, int);
}

#endif

