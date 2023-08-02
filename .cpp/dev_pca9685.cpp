/*
 * This file defines functions related with PCA9685.
 */
 
#include "dev_pca9685.h"
#include "libs/bcm2835_gpio/bcm2835.h"
using namespace std;

#define PCA9685_REG_MODE1                 0x00
#define PCA9685_REG_LED0_ON_L             0x06
#define PCA9685_REG_LED0_ON_H             0x07
#define PCA9685_REG_LED0_OFF_L            0x08
#define PCA9685_REG_LED0_OFF_H            0x09
#define PCA9685_REG_PRESCALE              0xFE


PCA9685::PCA9685(void)
{
    /* Initialize bcm2835 */
    if (! bcm2835_init()) {
        cout << "bcm2835_init() Failed." << endl;
    }

	/* Activate I2C */
	if (! bcm2835_i2c_begin()) {
		cout << "bcm2835_i2c_begin() Failed." << endl;
	}

	/* Set I2C */
	bcm2835_i2c_setSlaveAddress(0x40);
    bcm2835_i2c_setClockDivider(0x5dc);   // 166 KHz //
}

PCA9685::~ PCA9685(void)
{
    close(filename);
}

/* Write Value into Register */
void PCA9685::write(uint8_t reg, uint8_t value)
{
	char data[2];

	data[0] = reg;
	data[1] = value;
    bcm2835_i2c_write(data, 2);
}

/* Read Value from Register */
uint8_t PCA9685::read(uint8_t reg)
{
	uint8_t data;
	
	bcm2835_i2c_read_register_rs(reg, (char *)& data, 1);
    return data;
}

/* Set PWM Frequency */
void PCA9685::setPWMFreq(int freq)
{
    int prescale = 0;
	int old_mode = read(PCA9685_REG_MODE1);
	int new_mode = (old_mode & 0x7F) | 0x10;
	double temp = 25000000.0;
	
	temp /= 4096.0;
	temp /= (double) freq;
	temp -= 1.0;
	prescale = floor(temp + 0.5);
    
    write(PCA9685_REG_MODE1, new_mode);
    write(PCA9685_REG_PRESCALE, (int) floor(prescale));
    write(PCA9685_REG_MODE1, old_mode);
    usleep(5000);
    write(PCA9685_REG_MODE1, old_mode | 0x80);
}

/* Set PWM */
void PCA9685::setPWM(int channel, int on, int off)
{
    write(PCA9685_REG_LED0_ON_L + 4 * channel, on & 0xFF);
	write(PCA9685_REG_LED0_ON_H + 4 * channel, on >> 8);
	write(PCA9685_REG_LED0_OFF_L + 4 * channel, off & 0xFF);
	write(PCA9685_REG_LED0_OFF_H + 4 * channel, off >> 8);
}

/* Set DC Motor PWM */
void PCA9685::setMotorPWM(int channel, int duty) 
{
	setPWM(channel, 0, duty);
}

/* Set Servo Pulse */
void PCA9685::setServoPulse(int channel, int pulse) {
	int newPulse = (int) pulse * 4096 / 20000;
	
	setPWM(channel, 0, newPulse);
}

