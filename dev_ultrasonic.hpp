#ifndef _DEV_ULTRASONIC_HPP_
#define _DEV_ULTRASONIC_HPP_

#include "common.h"
#include "dev_motor.hpp"
#include "dev_servo.hpp"

# define MAX_DISTANCE       300

class ULTRASONIC {
    public :
        ULTRASONIC();
        ~ULTRASONIC();

        int getDistance();
    private:
        int pulseIn(int, int, int);
}

#endif
