#include "common.hpp"
#include "app_autoObstacleAvoidance.hpp"
#include "app_map.hpp"
#include "libs/timer/timer.hpp"
using namespace std;

APP_AUTO_OBSTACLE_AVOIDANCE Autorun;
APP_MAP Map;
TIMER SchedulerTimer;

void catchSIGINT(int signal);


void MainLoop(void)
{
    string instruction;
	ifstream file ("direction.txt");
	
	Autorun.run();
}

int main(int argc, char **argv)
{
    cout << "AutoRun program started." << endl;
    /*Init*/
    Autorun.setUp();
    
    /*Get direction*/
    Map.getDirection();
    
    /*Create timer*/
    SchedulerTimer.every(200, MainLoop, true);
    
    /*Create signal*/
    signal(SIGINT, catchSIGINT);
    
    /*Infinite loop*/
    while(1){
        SchedulerTimer.update();    
    }
    return 0;
}

/*Ctrl + C to exit testing*/
void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed, end program now..." << endl;
        exit(EXIT_SUCCESS);
	}
}

