#ifndef _TEST_HPP_
#define _TEST_HPP_

#include "common.h"
#include "dev_buzzer.hpp"
#include "dev_motor.hpp"
#include "dev_pca9685.hpp"
#include "dev_servo.hpp"
#include "dev_ultrasonic.hpp"



class TEST {
    public :
        TEST();
        ~TEST();

        int PCA9685_testInit();
        int PCA9685_test();

        int Buzzer_testInit();
        int Buzzer_test();

        int Motor_testInit();
        int Motor_test();

        int Servo_testInit();
        int Servo_test();

        int Ultrasonic_testInit();
        int Ultrasonic_test();

    private:
        BUZZER *test_buzzer;
        MOTOR *test_motor;
        SERVO *test_servo;
        ULTRASONIC *test_ultrasonic;

        uint8_t test_step;
        uint32_t test_cnter;
}

#endif