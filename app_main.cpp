#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include "common.h"
#include "app_autoRun.hpp"
#include "app_map.hpp"
#include "\libs\timer\timer.hpp"

using namespace std;

APP_AUTORUN Autorun;
APP_MAP Map;
Timer SchedulerTimer;

void MainLoop(void)
{
    Autorun.run();
}

int main(int argc, char **argv)
{
    cout << "AutoRun program started." << endl;
    Autorun.setUp();
    Map.getDirection();
    SchedulerTimer.every(200, MainLoop, true);
    signal(SIGINT, catchSIGINT);
    while(1){
        SchedulerTimer.update();    
    }
    return 0;
}

void catchSIGINT(int signal) {
	if (signal == SIGINT) {
		cout << "Ctrl + c Pressed, end program now..." << endl;
        exit(EXIT_SUCCESS);
	}
}




