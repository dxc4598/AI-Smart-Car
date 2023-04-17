# include <thread>
# include <iostream>
# include <signal.h>
# include <unistd.h>
# include "Motor.h"
# include "Servo.h"
# include "Buzzer.h"
# include "Ultrasonic.h"
using namespace std;

# define Servo_Min       0
# define Servo_Max      90
# define Min_Distance   20
# define Max_Distance   40


class AutoRun {
    public: 
        void stop();
        void goStraight(int);
        void turnLeft();
        void turnRight();
        void makeNoise(int);
        void setUp();
        void runServo(double, int);
        void checkDistance(double, int);
	
    private: 
        int L, M, R;
        float stopCount;
		
        Motor pwm;
        Servo pwmServo;
        Buzzer buzzer;
        Ultrasonic ultrasonic;
};


// Stop the car and cover the time loss in the process
void AutoRun::stop() {
    pwm.setMotorModel(0, 0, 0, 0);
    pwmServo.setServoPWM("0", 90);
    sleep(1);
    stopCount += 1;
}


void AutoRun::goStraight(int utime) {
    double t0;
    struct timeval tv0;
	
    stopCount = 0;
    gettimeofday(&tv0, NULL);
    t0 = tv0.tv_sec + tv0.tv_usec * 0.000001;
    
//  thread1: Control the servo to detect distances.
    thread thread1(&AutoRun::runServo, this, t0, utime);        
//  thread2: Control the motor by using the data got from the servo.
    thread thread2(&AutoRun::checkDistance, this, t0, utime);    
	
    thread1.join();
    thread2.join();
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
    stop();
}


// Call the buzzer
void AutoRun::makeNoise(int utime) {
    buzzer.makeSound("1");
    usleep(utime);
    buzzer.makeSound("0");
}


// Setup the car before running
void AutoRun::setUp() {
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
    makeNoise(500000);
}

// run the ultrasonic
void AutoRun::runServo(double t0, int utime) {
    double t1;
    struct timeval tv1;
	
    while (true) {
        for (int i = Servo_Min; i <= Servo_Max; i += (Servo_Max - Servo_Min)) {
            pwmServo.setServoPWM("0", i);
            usleep(200000);
			
            if (i == Servo_Min) {
                L = ultrasonic.getDistance();
                cout << "Left: " << L << " cm" << endl; 
            }
            else if (i == Servo_Max) {
                M = ultrasonic.getDistance();
                cout << "Middle: " << M << " cm" << endl; 
            }
        }
        // if run time is up, stop
        gettimeofday(&tv1, NULL);
        t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;
        if ((t1 - t0) > (utime * 0.000001 + stopCount * 1000000)) {
            pwmServo.setServoPWM("0", 90);
            break;
        }
    }
}

// run the motor
void AutoRun::checkDistance(double t0, int utime) {
    double t1;
    struct timeval tv1;
	
    while (true) {
        if (M < Min_Distance) {
            cout << "Middle Side is too Close." << endl;
            stop();
        }
        else if (L < Min_Distance) {
            cout << "Left Side is too Close." << endl;
            pwm.setMotorModel(2000, 2000, -500, -500);
            usleep(700000);
            pwm.setMotorModel(-500, -500, 2000, 2000);
            usleep(700000);
        
            pwm.setMotorModel(0, 0, 0, 0);
            stopCount += 0.5;
        }
        else if (L > Max_Distance) {
            cout << "Left Side is too Far." << endl;
            pwm.setMotorModel(-500, -500, 2000, 2000);
            usleep(700000);
            pwm.setMotorModel(2000, 2000, -500, -500);
            usleep(700000);
        
            pwm.setMotorModel(0, 0, 0, 0);
            stopCount += 0.5;
        }
        else {
            pwm.setMotorModel(600, 600, 600, 600);
        }
        // if run time is up, stop
        gettimeofday(&tv1, NULL);
        t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;
        if ((t1 - t0) > (utime * 0.000001 + stopCount * 1000000)) {
            pwm.setMotorModel(0, 0, 0, 0);
            break;
        }
    }
}
