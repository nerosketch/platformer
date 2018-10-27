/* 
 * File:   Btn.cpp
 * Author: ns
 * 
 * Created on October 24, 2018, 10:25 PM
 */

#include "Btn.h"
#include "resources.h"


Btn::Btn(string button_name)
{
    setResAnim(res::resources.getResAnim(button_name));
}

Btn::Btn(const Btn& orig)
{
}

Btn::~Btn()
{
}
