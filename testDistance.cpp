# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Servo.h"
# include "Ultrasonic.h"
using namespace std;

void catchSIGINT(int);

int main() {
    Servo pwmServo;
    Ultrasonic ultrasonic;
    int distance;
    
    signal(SIGINT, catchSIGINT);
    pwmServo.setServoPWM("0", 90);
    
    while (true) {
        distance = ultrasonic.getDistance();
        cout << "Obstacle distance is " << distance <<  "CM" << endl;
        sleep(1);
    }
}


void catchSIGINT(int signal) {
    if (signal == SIGINT) {
        cout << "Ctrl + c Pressed." << endl;
        exit(EXIT_SUCCESS);
    }
}
