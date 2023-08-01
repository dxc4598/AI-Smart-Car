#include "test.hpp"
#include "libs/bcm2835_gpio/bcm2835.h"

using namespace std;

TEST::TEST(void)
{
    test_buzzer = new BUZZER;
    test_motor = new MOTOR;
    test_servo = new SERVO;
    test_ultrasonic = new ULTRASONIC;

    test_step = 0;
    test_cnter = 0;
}

TEST::~ TEST(void)
{
    delete test_buzzer;
    delete test_motor;
    delete test_servo;
    delete test_ultrasonic;
}

/*I2C test, PCA9685 communication test*/
int TEST::PCA9685_testInit(void)
{
    int ret = 0;

    /*IO init*/
    if(! bcm2835_init()){
        cout << "bcm2835_init failed. Are you running as root??" << endl;
        ret = -1;
    }

    /*I2C begin*/
    if (!bcm2835_i2c_begin()){
        cout << "bcm2835_i2c_begin failed. Are you running as root??" << endl;
        ret = -1;
    }

    /*Config*/
    bcm2835_i2c_setSlaveAddress(0x40);
    bcm2835_i2c_setClockDivider(0x5dc); /*166KHz*/

    /**/
    test_step = 0;
    test_cnter = 0;

    return ret;
}

/*Run Freq: 1Sec*/
int TEST::PCA9685_test(void)
{
    int ret = 0;
    char read_data;

    /*Read Reg*/
    bcm2835_i2c_read_register_rs(0x05, &read_data, 1);

    /*Check data*/
    if(read_data != 0xE0)
        ret = -1;

    return ret;
}

/*Buzzer test*/
int TEST::Buzzer_testInit(void)
{
    int ret = 0;

    /**/
    test_step = 0;
    test_cnter = 0;

    return ret;
}

/*Run Freq: 1Sec*/
int TEST::Buzzer_test(void)
{
    static uint8_t flag = 0;
    int ret = 0;

    if(! flag){
        test_buzzer->makeSound(flag);
        flag = 1;
    }else{
        test_buzzer->makeSound(flag);
        flag = 0;
    }

    return ret;
}

/*Motor test*/

int TEST::Motor_testInit(void)
{
    int ret = 0;

    /**/
    test_step = 0;
    test_cnter = 0;

    return ret;
}

/*Run Freq: 1Sec*/
int TEST::Motor_test(void)
{
    int ret = 0;

    cout << "Motor.h Start Testing." << endl;

    switch(test_step){
        case 0 :
            test_motor->setMotorModel(1000, 1000, 1000, 1000); /* Move Forward. */
            cout << "Moving Forward." << endl;
            break;
        case 1 :
            test_motor->setMotorModel(-1000, -1000, -1000, -1000); /* Move Back. */
	        cout << "Moving Back." << endl;
            break;
        case 2 :
            test_motor->setMotorModel(-1500, -1500, 2000, 2000); /* Turn Left. */
	        cout << "Turning Left." << endl;
            break;
        case 3 :
            test_motor->setMotorModel(2000, 2000, -1500, -1500); /* Turn Right. */
	        cout << "Turning Right." << endl; 
            break;
        case 4 :
            test_motor->setMotorModel(0, 0, 0, 0); /* End testing*/
	        cout << "End testing." << endl; 
            break;
        default :
            break; 
    }

    if(test_step < 4)
        test_step ++;
    else
        ; /*Wait forever*/

    return ret;
}

/*Servo test*/

int TEST::Servo_testInit(void)
{
    int ret = 0;

    test_step = 0;
    test_cnter = 0;

    return ret;
}

/*Run Freq: 10 mSec*/
int TEST::Servo_test(void)
{
    int ret = 0;

    switch (test_step)
    {
        case 0:
            test_cnter = 50;
            test_step ++;
            break;
        case 1 :
            test_servo->setServoPWM(0, test_cnter);
            if(test_cnter < 110)
                test_cnter ++;
            else{
                test_cnter = 110;
                test_step ++;
            }

            break;
        case 2 :
            test_servo->setServoPWM(0, test_cnter);
            if(test_cnter > 50)
                test_cnter --;
            else{
                test_cnter = 80;
                test_step ++;
            }

            break;
        case 3 :
            test_servo->setServoPWM(1, test_cnter);
            if(test_cnter < 150)
                test_cnter ++;
            else{
                test_cnter = 150;
                test_step ++;
            }
            break;
        
        case 5 :
            test_servo->setServoPWM(1, test_cnter);
            if(test_cnter > 80)
                test_cnter --;
            else{
                test_cnter = 0;
                test_step ++;
            }
            break;
        case 6 :
            break; /*Wait forever*/
        default:
            break;
    }

    return ret;
}

/*Ultrasonic test*/

int TEST::Ultrasonic_testInit(void)
{
    int ret = 0;

    test_step = 0;
    test_cnter = 0;

    return ret;
}

/*Run Freq: 1 Sec*/
int TEST::Ultrasonic_test(void)
{
    int ret = 0;
    int distance;
    
    distance = test_ultrasonic->getDistance();
    cout << "Ultrasonic Test, Distance = " << distance << "." << endl;

    return ret;
}




