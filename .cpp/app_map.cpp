/* 
 * This file defines functions to get diretions from Google Map.
 */

#include "app_map.hpp"
#include "libs/googlemap/api.hpp"

#define OUTPUT_FILENAME     "directions.txt"

using namespace Google::Maps;
using namespace cURLpp;
using namespace std;


APP_MAP::APP_MAP(void)
{
    long flags;

    /* Initialize cURL */
    flags = CURL_GLOBAL_ALL;
    cURLpp::initialize(flags);
    
    outfile.open(OUTPUT_FILENAME);
    outfile << "Google Map API Initialization Completed." << endl;
    outfile.close();
}

APP_MAP::~ APP_MAP(void)
{
    cURLpp::terminate();
}

/* Get Directions */
void APP_MAP:getDirection(void)
{
    outfile.open(OUTPUT_FILENAME);
    
    /* Connect to Google Map */
    try{
        points origin = "place_id:ChIJg4R3aQVFiEgRz8dmd7akBmE";        /* Accommodation, 31 Dunblane Street, Glasgow, G4 0HJ */
        points destination = "place_id:ChIJJYXx7yBEiEgR76XjNOUkIrk";   /* McDonald's, 101, 105 Sauchiehall Street, Glasgow, G2 3DD */
    
        try{
            API:client maps ("AIzaSyDLnexJ5T_CKi1IHuzb4o7j1R1yJdIooF0");
            try{
                outfile << maps.direction (API::output_format_t ("json"), origin, destination) << "\n"; 
				outfile << maps.direction (origin, destination) << "\n"; 
            }
			catch(std::exception & e){
                outfile << e.what ();
            }
        }
		catch(std::exception & e){
            outfile << e.what ();
        }
    }
	catch(std::exception & e){
        outfile << e.what ();
    }

    outfile.close();
}

