/******************************************************************************************************************
 * File name      : timer
 * Description    : Timer
 * Author         : 
 * Create Date    : 2023-07-21
 * Modify history : 
 * 
 * 
 * 
*****************************************************************************************************************/
#include "timer.h"

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <chrono>
#include <ctime>

/****************************************************************************************************************/
TIMER::TIMER(void)
{

}

TIMER::~ TIMER(void)
{

}

/****************************************************************************************************************/
/*period: milliseconds*/
void TIMER::create(unsigned long period, void (*callback)(),bool start)
{
	struct timeval tv;

	gettimeofday (&tv, NULL) ;
    this->epochMilli = (uint64_t)tv.tv_sec * (uint64_t)1000    + (uint64_t)(tv.tv_usec / 1000) ;
    this->epochMicro = (uint64_t)tv.tv_sec * (uint64_t)1000000 + (uint64_t)(tv.tv_usec) ;
	
	this->period = period;
	this->callback = callback;
	this->lastEventTime = millis();
	this->is_working = start;
}

void TIMER::setPeriod(unsigned long period)
{
	this->period = period;
}

void TIMER::stop()
{
	this->is_working = false;
}

void TIMER::start()
{
	this->is_working = true;
}

unsigned int TIMER::millis()
{
    uint64_t now;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    now  = (uint64_t)tv.tv_sec * (uint64_t)1000 + (uint64_t)(tv.tv_usec / 1000);

    return (uint32_t)(now - this->epochMilli);
}

void TIMER::update()
{
	if(this->is_working == true){
		unsigned long now = millis();
		if (now - this->lastEventTime >= this->period){
			(*callback)();
			this->lastEventTime = now;
		}
    }
}





