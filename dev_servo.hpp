/******************************************************************************************************************
 * The purpose of this function is to drive the servo motor of the car
*****************************************************************************************************************/
#ifndef _DEV_SERVO_HPP_
#define _DEV_SERVO_HPP_

#include "common.h"
#include "dev_pca9685.h"

class SERVO {
    public :
        SERVO();
        ~SERVO();

        void setServoPWM(string, double, int);
    private:
        PCA9685 pwmServo;
}

#endif
