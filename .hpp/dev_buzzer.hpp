/* 
 * This file defines functions to control the buzzer of the car.
 */

#ifndef _DEV_BUZZER_HPP_
#define _DEV_BUZZER_HPP_

#include "common.h"


class BUZZER {
    public:
        BUZZER();
        ~BUZZER();

        void makeSound(string);
    private:
}

#endif

