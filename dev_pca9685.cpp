/*
 * This file defines some functions related with PCA9685.
 */
#include "dev_pca9685.h"
#include <i2c/smbus.h>

using namespace std;

#define PCA9685_REG_MODE1                 0x00
#define PCA9685_REG_LED0_ON_L             0x06
#define PCA9685_REG_LED0_ON_H             0x07
#define PCA9685_REG_LED0_OFF_L            0x08
#define PCA9685_REG_LED0_OFF_H            0x09
#define PCA9685_REG_PRESCALE              0xFE


PCA9685::PCA9685(void)
{
    /*Open I2C device file*/
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);

    /*Check I2C device file*/
    cout << "File Route: " << filename << endl;
	
	if (file < 0) {
		cout << "File Open Failed." << endl;
		exit(EXIT_FAILURE);
	} 
	else {
		cout << "File Open Successed." << endl;
	}
	
	if (ioctl(file, I2C_SLAVE, address) < 0) {
        cout << "Set ioctl Failed." << endl;
        exit(EXIT_FAILURE);
    }
    else {
    	cout << "Set ioctl Successed." << endl;
	}
}

PCA9685::~ PCA9685(void)
{
    close(filename);
}

void PCA9685::write(int reg, int value)
{
    i2c_smbus_write_byte_data(file, reg, value);
}

int PCA9685::read(int reg)
{
    return i2c_smbus_read_byte_data(file, reg);
}

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

void PCA9685::setPWM(int channel, int on, int off)
{
    write(PCA9685_REG_LED0_ON_L + 4 * channel, on & 0xFF);
	write(PCA9685_REG_LED0_ON_H + 4 * channel, on >> 8);
	write(PCA9685_REG_LED0_OFF_L + 4 * channel, off & 0xFF);
	write(PCA9685_REG_LED0_OFF_H + 4 * channel, off >> 8);
}

void PCA9685::setMotorPWM(int channel, int duty) 
{
	setPWM(channel, 0, duty);
}

void PCA9685::setServoPulse(int channel, int pulse) {
	int newPulse = (int) pulse * 4096 / 20000;
	
	setPWM(channel, 0, newPulse);
}

