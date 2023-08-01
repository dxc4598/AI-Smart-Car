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
#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include "common.h"
#include <inttypes.h>

/****************************************************************************************************************/


/****************************************************************************************************************/
class TIMER {
    public :
        TIMER();
        ~TIMER();

        void create (unsigned long, void *, bool);
        void setPeriod(unsigned long period);
        void stop();
        void start();
        void update();
    private:
        unsigned long period;
        unsigned long lastEventTime;
        void (*callback)(void);
        bool is_working;
        
        uint64_t epochMilli,epochMicro;
}

#endif
