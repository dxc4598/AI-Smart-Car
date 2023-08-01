#ifndef _DEV_MOTOR_HPP_
#define _DEV_MOTOR_HPP_

#include "common.h"
#include "dev_pca9685.h"

class MOTOR {
    public :
        MOTOR();
        ~MOTOR();

        void setMotorModel(int, int, int, int);

    private:
        PCA9685 pwm;
		
		void setDutyRange(int, int, int, int);
		void setLeftUpperWheel(int);
		void setLeftLowerWheel(int);
		void setRightUpperWheel(int);
		void setRightLowerWheel(int);
}

#endif