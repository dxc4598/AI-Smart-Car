// Raspi PCA9685 16-Channel PWM Servo Driver
# pragma once

# include <cmath>
# include <cstdio>
# include <cstdlib>
# include <iostream>
# include <fcntl.h>
# include <unistd.h>
# include <sys/ioctl.h>

extern "C" {
    #include <linux/i2c-dev.h>
    #include <i2c/smbus.h>
}
using namespace std;

// Registers
# define __MODE1         0x00
# define __LED0_ON_L     0x06
# define __LED0_ON_H     0x07
# define __LED0_OFF_L    0x08
# define __LED0_OFF_H    0x09
# define __PRESCALE      0xFE


class PCA9685 {
	public:
    	PCA9685();
    
		int read(int);
		void write(int, int);
		void setPWMFreq(int);
		void setPWM(int, int, int);
		void setMotorPWM(int, int);
		void setServoPulse(int, int);
		
	private: 
      	int file;
    	int adapter_nr = 1;
    	int address = 0x40;
    	char filename[20];
    	
    	void getFile();
    	void checkFile();
};


PCA9685::PCA9685() {
    getFile();
    checkFile();
    
    write(__MODE1, 0x00);
}


void PCA9685::getFile() {
	snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
}


void PCA9685::checkFile() {
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

// Write an 8-bit value to the specified register/address
void PCA9685::write(int reg, int value) {
	i2c_smbus_write_byte_data(file, reg, value);
}

// Read an unsigned byte from the I2C device
int PCA9685::read(int reg) {
	int result = i2c_smbus_read_byte_data(file, reg);
	
	return result;
}

// Set the PWM frequency
void PCA9685::setPWMFreq(int freq) {
	int prescale = 0;
	int old_mode = read(__MODE1);
	int new_mode = (old_mode & 0x7F) | 0x10;
	double temp = 25000000.0;
	
	temp /= 4096.0;
	temp /= (double) freq;
	temp -= 1.0;
	prescale = floor(temp + 0.5);
    
    write(__MODE1, new_mode);
    write(__PRESCALE, (int) floor(prescale));
    write(__MODE1, old_mode);
    usleep(5000);
    write(__MODE1, old_mode | 0x80);
}

// Set a single PWM channel
void PCA9685::setPWM(int channel, int on, int off) {
	write(__LED0_ON_L + 4 * channel, on & 0xFF);
	write(__LED0_ON_H + 4 * channel, on >> 8);
	write(__LED0_OFF_L + 4 * channel, off & 0xFF);
	write(__LED0_OFF_H + 4 * channel, off >> 8);
}


void PCA9685::setMotorPWM(int channel, int duty) {
	setPWM(channel, 0, duty);
}

// Set the Servo Pulse, The PWM frequency must be 50HZ
void PCA9685::setServoPulse(int channel, int pulse) {
	int newPulse = (int) pulse * 4096 / 20000;
	
	setPWM(channel, 0, newPulse);
}
