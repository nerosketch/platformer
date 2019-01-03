/* 
 * File:   Btn.cpp
 * Author: ns
 * 
 * Created on October 24, 2018, 10:25 PM
 */

#include "resources.h"
#include "Btn.h"


Btn::Btn(string button_name)
{
    setResAnim(res::resources.getResAnim(button_name));
}

Btn::Btn(const Btn&)
{}

Btn::~Btn()
{}
