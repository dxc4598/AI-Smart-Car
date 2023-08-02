/*
 * This file defines functions related with PCA9685.
 */
 
#ifndef _DEV_PCA9685_HPP_
#define _DEV_PCA9685_HPP_

#include "common.h"


class PCA9685 {
    public:
        PCA9685();
        ~PCA9685();

        void setPWMFreq(int);
		void setMotorPWM(int, int);
		void setServoPulse(int, int);

    private:
        char filename[32];
        
        int read(int);
		void write(int, int);
		void setPWM(int, int, int);
}

#endif

