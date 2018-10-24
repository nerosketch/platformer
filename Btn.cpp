/* 
 * File:   Btn.cpp
 * Author: ns
 * 
 * Created on October 24, 2018, 10:25 PM
 */

#include "Btn.h"
#include "resources.h"


Btn::Btn()
{
    setResAnim(res::resources.getResAnim("Add"));
}

Btn::Btn(const Btn& orig)
{
}

Btn::~Btn()
{
}
