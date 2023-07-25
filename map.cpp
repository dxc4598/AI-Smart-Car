/******************************************************************************************************************
 * The purpose of this feature is to connect to Google Maps
*****************************************************************************************************************/
#include "map.h"
#include "libs/googlemap/api.hpp"

using namespace Google::Maps;

MAP::MAP(void)
{
    FILE *log_file;

    log_file = fopen("direction.txt", "w");

    point AI_SmartCar ("AI_SmartCar");


    fwrite("stop");
    fclose(log_file);
}

MAP::~ MAP(void)
{

}

