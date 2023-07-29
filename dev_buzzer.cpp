#include "dev_buzzer.h"
#include "libs/bcm2835_gpio/bcm2835.h"

#define BUZZER_PIN              17

BUZZER::BUZZER(void)
{
    /*IO init*/
    bcm2835_init();

    /*Set IO direction*/
    bcm2835_gpio_fsel(BUZZER_PIN, BCM2835_GPIO_FSEL_OUTP);
}

BUZZER::~ BUZZER(void)
{

}

void BUZZER::makeSound(string command) 
{
    if (command == "0") {
        bcm2835_gpio_write(BUZZER_PIN, LOW);
    }else if (command == "1") {
        bcm2835_gpio_write(BUZZER_PIN, HIGH);
    }
}

