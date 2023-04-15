# pragma once

# include <iostream>
# include <algorithm>
# include <unistd.h>
# include <wiringPi.h>
# include <sys/time.h>
# include "Motor.h"
# include "Servo.h"
using namespace std;

# define Echo_Pin      22
# define Trigger_Pin   27
# define MAX_DISTANCE  300
# define MAX_TIMEOUT   300 * 60


class Ultrasonic {
    public: 
        Ultrasonic();
        
        int getDistance();
        void setRun();

    private: 
        Motor pwm;
        Servo pwmServo;

        int pulseIn(int, int, int);
        void runMotor(int, int, int);
};


Ultrasonic::Ultrasonic(void) {
    wiringPiSetupGpio();
    pinMode(Echo_Pin, INPUT);
    pinMode(Trigger_Pin, OUTPUT);
}


int Ultrasonic::pulseIn(int pin, int level, int timeout) {
    int pulse_time = 0;
    double t0, t1;
    struct timeval tv0, tv1;
    
    gettimeofday(&tv0, NULL);
    t0 = tv0.tv_sec + tv0.tv_usec * 0.000001;

    while (digitalRead(pin) != level) {
        gettimeofday(&tv1, NULL);
        t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;

        if ((t1 - t0) > MAX_TIMEOUT * 0.000001) {
            return 0;
        }
    }

    gettimeofday(&tv0, NULL);
    t0 = tv0.tv_sec + tv0.tv_usec * 0.000001;
    while (digitalRead(pin) == level) {
        gettimeofday(&tv1, NULL);
        t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;

        if ((t1 - t0) > MAX_TIMEOUT * 0.000001) {
            return 0;
        }
    }

    gettimeofday(&tv1, NULL);
    t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;
    pulse_time = (t1 - t0) * 1000000;

    return pulse_time;
}


int Ultrasonic::getDistance() {
    double distance[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

    for (int i = 0; i < 5; i++) {
        digitalWrite(Trigger_Pin, HIGH);
        usleep(10);
        digitalWrite(Trigger_Pin, LOW);

        int pulse_time = pulseIn(Echo_Pin, HIGH, MAX_TIMEOUT);
        distance[i] = pulse_time * 340.0 / 2.0 / 10000.0;
    }

    sort(distance, distance + 5);
    return (int) distance[2];
}


void Ultrasonic::setUp() {
    int L, M, R;

    for (int i = 30; i < 151; i += 60) {
        pwmServo.setServoPWM("0", i);
        usleep(200000);

        if (i == 30) {
            L = getDistance();
            cout << "Left Side Distance is " << L << " cm" << endl; 
        }
        else if (i == 90) {
            M = getDistance();
            cout << "Middle Side Distance is " << M << " cm" << endl; 
        }
        else {
            R = getDistance();
            cout << "Right Side Distance is " << R << " cm" << endl; 
        }
    }
}


void Ultrasonic::runMotor(int L, int M, int R) {
    if (((L < 30) && (M < 30) && (R < 30)) || M < 30 ) {
        pwm.setMotorModel(-1450, -1450, -1450, -1450);
        usleep(100000);

        if (L < R) {
            pwm.setMotorModel(1450, 1450, -1450, -1450);
        } 
        else {
            pwm.setMotorModel(-1450, -1450, 1450, 1450);
        }
    }
    else if ((L < 30) && (M < 30)) {
        pwm.setMotorModel(1500, 1500, -1500, -1500);
    }
    else if ((R < 30) && (M < 30)) {
        pwm.setMotorModel(-1500, -1500, 1500, 1500);
    }
    else if (L < 20) {
        pwm.setMotorModel(2000, 2000, -500, -500);

        if (L < 10) {
            pwm.setMotorModel(1500, 1500, -1000, -1000);
        }
    }
    else if (R < 20) {
        pwm.setMotorModel(-500, -500, 2000, 2000);

        if (R < 10) {
            pwm.setMotorModel(-1500, -1500, 1500, 1500);
        }
    }
    else {
        pwm.setMotorModel(600, 600, 600, 600);
    }
}


void Ultrasonic::run() {
    int L, M, R;

    for (int i = 90; i > 29; i -= 60) {
        pwmServo.setServoPWM("0", i);
        usleep(200000);
        
        if (i == 30) {
            L = getDistance();
        }
        else if (i == 90) {
            M = getDistance();
        }
        else {
            R = getDistance();
        }
        
        runMotor(L, M, R);
    }

    for (int i = 30; i < 151; i += 60) {
        pwmServo.setServoPWM("0", i);
        usleep(200000);

        if (i == 30) {
            L = getDistance();
        }
        else if (i == 90) {
            M = getDistance();
        }
        else {
            R = getDistance();
        }
        
        runMotor(L, M, R);
    }
}
