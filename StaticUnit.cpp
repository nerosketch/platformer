/* 
 * File:   StaticUnit.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:46 AM
 */

#include "StaticUnit.h"

StaticUnit::StaticUnit(const Vector2& pos) :
Unit(pos)
{
}

StaticUnit::StaticUnit(const StaticUnit& orig):
StaticUnit(orig.getPosition())
{
}

StaticUnit::~StaticUnit() {
}

