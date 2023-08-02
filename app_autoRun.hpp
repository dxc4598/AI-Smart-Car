/* 
 * This file defines functions to control the behavior of the car.
 */

#ifndef _APP_AUTORUN_HPP_
#define _APP_AUTORUN_HPP_

#include "common.h"
#include "dev_buzzer.hpp"
#include "dev_motor.hpp"
#include "dev_servo.hpp"
#include "dev_ultrasonic.hpp"


class APP_AUTORUN {
    public :
        APP_AUTORUN();
        ~APP_AUTORUN();

        void setUp();
        void run();
    private:
        BUZZER *Buzzer;
        MOTOR *Motor;
        SERVO *Servo;
        ULTRASONIC *Ultrasonic;

        uint8_t run_step;
}

#endif

