/* 
 * File:   resources.h
 * Author: ns
 *
 * Created on July 18, 2018, 12:26 AM
 */

#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <oxygine-framework.h>


using namespace std;
using namespace oxygine;


namespace res
{
    extern Resources resources;
    void load(const string&);
    void free();
}


#endif /* RESOURCES_H */
