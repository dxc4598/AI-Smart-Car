# include <iostream>
# include <unistd.h>
# include "Motor.h"
# include "Servo.h"
# include "Buzzer.h"
# include "Ultrasonic.h"
# include <signal.h>
using namespace std;

# define Servo_Min      0
# define Servo_Max      90
# define Min_Distance   50
# define Max_Distance  200


class AutoRun {
    public: 
        void stop();
        void goStraight(int);
        void turnLeft();
        void turnRight();
        void runServo();
        void makeNoise(int);
        void setUp();
        void checkDistance();

    private: 
        int L = 100, M = 100, R = 100, stopCount = 0;
        bool isRunning = true;
        
        Motor pwm;
        Servo pwmServo;
        Buzzer buzzer;
        Ultrasonic ultrasonic;
};


void AutoRun::stop() {
    pwm.setMotorModel(0, 0, 0, 0);
    pwmServo.setServoPWM("0", 90);
    sleep(1);
    
    while (true) {
        if (!isRunning) {
            stopCount += 1;
        }
        else {
            stopCount = 0;
            break;
        }
    }
}


void AutoRun::goStraight(int utime) {
    double t0, t1;
    struct timeval tv0, tv1;

    gettimeofday(&tv0, NULL);
    t0 = tv0.tv_sec + tv0.tv_usec * 0.000001;
    while (true) {
        runServo();
        checkDistance();
        
        gettimeofday(&tv1, NULL);
        t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;
        if ((t1 - t0) > (utime * 0.000001 + stopCount * 1000000) {
            stop();
            break;
        }
    }
}


void AutoRun::turnLeft() {
    makeNoise(250000);
    pwm.setMotorModel(-1500, -1500, 2000, 2000);
    sleep(1);
    stop();
}


void AutoRun::turnRight() {
    makeNoise(250000);
    pwm.setMotorModel(2000, 2000, -1500, -1500);
    sleep(1);
}


void AutoRun::runServo() {
    pwmServo.setServoPWM("0", Servo_Min);
    L = ultrasonic.getDistance();
    usleep(200000);

    pwmServo.setServoPWM("0", Servo_Max);
    M = ultrasonic.getDistance();
    usleep(200000);
    
    
}


void AutoRun::makeNoise(int utime) {
    buzzer.makeSound("1");
    usleep(utime);
    buzzer.makeSound("0");
}


void AutoRun::setUp() {
    ultrasonic.setUp();
    for (int i = 30; i < 151; i += 60) {
        pwmServo.setServoPWM("0", i);
        usleep(200000);

        if (i == 30) {
            L = ultrasonic.getDistance();
            cout << "Left: " << L << " cm" << endl; 
        }
        else if (i == 90) {
            M = ultrasonic.getDistance();
            cout << "Middle: " << M << " cm" << endl; 
        }
        else {
            R = ultrasonic.getDistance();
            cout << "Right: " << R << " cm" << endl; 
        }
    }

    cout << "Smart Car has Set Up." << endl;
    cout << "-------------------------------" << endl;
    checkDistance();
    makeNoise(500000);
}


void AutoRun::checkDistance() {
    if (M < Min_Distance) {
        isRunning = false;
        stop();
        cout << "Middle Side is too Close." << endl;
    }
    else if (L < Min_Distance) {
        isRunning = false;
        stop();
        cout << "Left Side is too Close." << endl;
    }
    else if (R < Min_Distance) {
        isRunning = false;
        stop();
        cout << "Right Side is too Close." << endl;
    }
    else if (L < (Min_Distance - 10)) {
        pwm.setMotorModel(2000, 2000, -500, -500);

        if (L < (Min_Distance - 20)) {
            pwm.setMotorModel(1500, 1500, -1000, -1000);
        }
    }
    else if (L > (Max_Distance)) {
        pwm.setMotorModel(-500, -500, 2000, 2000);
    }
    else {
        pwm.setMotorModel(600, 600, 600, 600);
}
