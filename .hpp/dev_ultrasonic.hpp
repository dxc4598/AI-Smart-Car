/* 
 * This file defines functions to control the ultrasonic of the car.
 */

#ifndef _DEV_ULTRASONIC_HPP_
#define _DEV_ULTRASONIC_HPP_

#include "common.h"
#include "dev_servo.h"

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
