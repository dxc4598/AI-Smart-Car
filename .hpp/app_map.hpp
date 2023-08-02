/* 
 * This file defines functions to get diretions from Google Map.
 */

#ifndef _APP_MAP_HPP_
#define _APP_MAP_HPP_

#include "common.hpp"
#include <iostream>
#include <fstream>


class APP_MAP {
    public :
        APP_MAP();
        ~APP_MAP();

        void getDirection(void);
    private:
        ofstream outfile;
}

#endif

