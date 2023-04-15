# include <iostream>
# include <unistd.h>
# include "Motor.h"
# include "Servo.h"
# include "Buzzer.h"
# include "Ultrasonic.h"
using namespace std;

# define Servo_Min      5
# define Servo_Max      90
# define Min_Distance   25
# define Max_Distance  200


class AutoRun {
    public: 
        AutoRun();

        void stop();
        void goStraight(int);
        void turnLeft();
        void turnRight();
        void runServo();
        void setUp();
        void makeNoise(int);
        void checkDistance();

    private: 
        int L, M;
        int R = 75;

        Motor pwm;
        Servo pwmServo;
        Buzzer buzzer;
        Ultrasonic ultrasonic;
};


AutoRun::AutoRun(void) {
}


void AutoRun::stop() {
    pwm.setMotorModel(0, 0, 0, 0);
    pwmServo.setServoPWM("0", 90);
    sleep(1);
}


void AutoRun::goStraight(int time) {
    double t0, t1;
    struct timeval tv0, tv1;

    gettimeofday(&tv0, NULL);
    t0 = tv0.tv_sec + tv0.tv_usec * 0.000001;
    
    while (true) {
        runServo();
        checkDistance();
        
        gettimeofday(&tv1, NULL);
        t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;
        if ((t1 - t0) > time * 0.000001) {
            stop();
            break;
        }
    }
}


void AutoRun::turnLeft() {
    makeNoise(500000);
    pwm.setMotorModel(-1500, -1500, 2000, 2000);
    sleep(1);
    stop();
}


void AutoRun::turnRight() {
    makeNoise(500000);
    pwm.setMotorModel(2000, 2000, -1500, -1500);
    sleep(1);
    stop();
}


void AutoRun::runServo() {
    pwmServo.setServoPWM("0", Servo_Min);
    L = ultrasonic.getDistance();
    usleep(200000);

    pwmServo.setServoPWM("0", Servo_Max);
    M = ultrasonic.getDistance();
    usleep(200000);
    
    
}


void AutoRun::makeNoise(int noise_time) {
    buzzer.makeSound("1");
    usleep(noise_time);
    buzzer.makeSound("0");
}


void AutoRun::setUp() {
    ultrasonic.setUp();
    makeNoise(500000);
}


void AutoRun::checkDistance() {
    cout << "L is " << L << endl;
    cout << "M is " << M << endl;
    
    if (L < Min_Distance) {
        cout << "Left Side is too Close." << endl;
        stop();
    }
    else if (M < Min_Distance) {
        cout << "Middle Side is too Close." << endl;
        stop();
    }
    else if (R < Min_Distance) {
        cout << "Right Side is too Close." << endl;
        stop();
    }
    else pwm.setMotorModel(600, 600, 600, 600);
}
