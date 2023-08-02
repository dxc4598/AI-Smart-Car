/*
 * This file is the main file for the car to run indoor.
 */

#include "common.hpp"
#include "app_autoObstacleAvoidance.hpp"
#include "libs/timer/timer.hpp"
using namespace std;

APP_AUTO_OBSTACLE_AVOIDANCE Autorun;
APP_MAP Map;
TIMER SchedulerTimer;

void catchSIGINT(int signal);


void MainLoop(void)
{
	Autorun.run();
}

int main(int argc, char **argv)
{
    cout << "Indoor Program Started." << endl;
    
    /* Initialize */
    Autorun.setUp();
    
    /* Create Timer */
    SchedulerTimer.every(200, MainLoop, true);
    
    /* Get Signal */
    signal(SIGINT, catchSIGINT);
    
    while(1) {
        SchedulerTimer.update();    
    }
    
    return 0;
}

/* Ctrl + c to Exit */
void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed, End Program Now..." << endl;
        exit(EXIT_SUCCESS);
	}
}

