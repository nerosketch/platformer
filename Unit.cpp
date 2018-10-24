/* 
 * File:   Unit.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:45 AM
 */

#include "Unit.h"

Unit::Unit(const Vector2& pos):
_pos(pos)
{
    setPosition(pos);
}

Unit::Unit(const Unit& orig)
{
}

Unit::~Unit()
{
}

void Unit::doUpdate(const UpdateState& us)
{
    setPosition(_pos);
}
