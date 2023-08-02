/* 
 * This file defines functions to control the ultrasonic of the car.
 */

#include "dev_ultrasonic.h"
#include "libs/bcm2835_gpio/bcm2835.h"
# include <sys/time.h>
# include <algorithm>
using namespace std;

# define Echo_Pin            22
# define Trigger_Pin         27
# define MAX_TIMEOUT   300 * 60


ULTRASONIC::ULTRASONIC(void)
{
	/* Initialize bcm2835 */
    if(! bcm2835_init()){
        cout << "bcm2835_init() Failed." << endl;
    }

    /* Set Echo Pin as Input */
    bcm2835_gpio_fsel(Echo_Pin, BCM2835_GPIO_FSEL_INPT);

    /* Set Trigger Pin as Output */
    bcm2835_gpio_fsel(Trigger_Pin, BCM2835_GPIO_FSEL_OUTP);
}

ULTRASONIC::~ ULTRASONIC(void)
{

}

/* Get the round-trip time of the pulse */
int ULTRASONIC::pulseIn(int pin, int level, int timeout)
{
    int pulse_time = 0;
    double t0, t1;
    struct timeval tv0, tv1;
	
    gettimeofday(&tv0, NULL);
    t0 = tv0.tv_sec + tv0.tv_usec * 0.000001;

    while (bcm2835_gpio_lev(pin) != level) {
        gettimeofday(&tv1, NULL);
        t1 = tv1.tv_sec + tv1.tv_usec * 0.000001;
		
        if ((t1 - t0) > MAX_TIMEOUT * 0.000001) {
            return 0;
        }
    }
	
    gettimeofday(&tv0, NULL);
    t0 = tv0.tv_sec + tv0.tv_usec * 0.000001;
    while (bcm2835_gpio_lev(pin) == level) {
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

/* Get the distance between the car and the obstacle */
int ULTRASONIC::getDistance()
{
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

