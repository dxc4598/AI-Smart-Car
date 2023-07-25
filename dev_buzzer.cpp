#include <wiringPi.h>

BUZZER::BUZZER(void)
{
	wiringPiSetupGpio();
    pinMode(Buzzer_Pin, OUTPUT);
}

BUZZER::~ BUZZER(void)
{

}


void BUZZER::makeSound(string command) 
{
    if (command == "0") {
        digitalWrite(Buzzer_Pin, LOW);
    }else if (command == "1") {
        digitalWrite(Buzzer_Pin, HIGH);
    }
}