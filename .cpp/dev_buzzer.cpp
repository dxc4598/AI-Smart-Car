/* 
 * This file defines functions to control the buzzer of the car.
 */

#include "dev_buzzer.hpp"
#include "libs/bcm2835_gpio/bcm2835.h"

#define BUZZER_PIN            17


BUZZER::BUZZER(void)
{
    /* Initialize bcm2835 */
    bcm2835_init();

    /* Set Buzzer Pin as Output */
    bcm2835_gpio_fsel(BUZZER_PIN, BCM2835_GPIO_FSEL_OUTP);
}

BUZZER::~ BUZZER(void)
{

}

/* Control the Buzzer */
void BUZZER::control(uint8_t enable) 
{
    if (enable == 0) {
        bcm2835_gpio_write(BUZZER_PIN, LOW);
    }else {
        bcm2835_gpio_write(BUZZER_PIN, HIGH);
    }
}

