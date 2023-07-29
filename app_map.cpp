#include "app_map.h"
#include "libs/googlemap/api.hpp"

#define OUTPUT_FILENAME     "directions.txt"

using namespace Google::Maps;
using namespace cURLpp;
using namespace std;

APP_MAP::APP_MAP(void)
{
    cURLpp::initialize(long flags = cURLpp :: CURL_GLOBAL_ALL);
    outfile.open(OUTPUT_FILENAME);
    outfile << "Google Map API init completed!" << endl;
    outfile.close();
}

APP_MAP::~ APP_MAP(void)
{
    cURLpp::terminate();
}

void APP_MAP:getDirection(void)
{
    outfile.open(OUTPUT_FILENAME);
    try{
        points origin = "place_id:ChIJg4R3aQVFiEgRz8dmd7akBmE";
        points destination = "place_id:ChIJJYXx7yBEiEgR76XjNOUkIrk";
    
        try{
            API:client maps ("AIzaSyDLnexJ5T_CKi1IHuzb4o7j1R1yJdIooF0");
            try{
                outfile << maps.direction (API::output_format_t ("json"), origin, destination) << "\n"; 
				outfile << maps.direction (origin, destination) << "\n"; 
            }catch(std::exception & e){
                outfile << e.what ();
            }
        }catch(std::exception & e){
            outfile << e.what ();
        }
    }catch(std::exception & e){
        outfile << e.what ();
    }

    /*Close file*/
    outfile << "End" << endl;
    outfile.close();
}





