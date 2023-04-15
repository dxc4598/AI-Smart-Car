# include <iostream>
# include <unistd.h>
# include "Motor.h"
# include "Servo.h"
# include "Buzzer.h"
# include "Ultrasonic.h"
using namespace std;

# define Servo_Min      30
# define Servo_Max      90
# define Min_Distance   50
# define Max_Distance  200


class AutoRun {
    public: 
        AutoRun();

        void stop()
        void goStraight(int);
        void turnLeft();
        void turnRight();
        void setServo();

    private: 
        int L, M, R;

        Motor pwm;
        Servo pwmServo;
        Buzzer buzzer;
        Ultrasonic ultrasonic;
};


AutoRun::AutoRun() {
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
        pwm.setMotorModel(1200, 1200, 1200, 1200);

        gettimeofday(&tv1, NULL);
        t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;
        if ((t1 - t0) > time * 0.000001) {
            stop();
            break;
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
}


void AutoRun::runServo() {
    for (int i = Servo_Min; i <= Servo_Max; i++) {
        pwm.setServoPWM("0", i);
        usleep(10000);
    }
    for (int i = Servo_Max; i >= Servo_Min; i--) {
        pwm.setServoPWM("0", i);
        usleep(10000);
    }
}


void AutoRun::makeNoise(int noise_time) {
    buzzer.makeSound("1");
    usleep(noise_time);
    buzzer.makeSound("0");
}


void AutoRun::setUp() {
    ultrasonic.setUp();
    checkDistance();
    makeNoise(500000);
}


void AutoRun::checkDistance() {
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
}
