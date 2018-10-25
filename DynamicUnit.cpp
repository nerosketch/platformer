/* 
 * File:   DynamicUnit.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:47 AM
 */

#include "DynamicUnit.h"


#ifdef DBG
#include <iostream>
#endif


DynamicUnit::DynamicUnit(const Vector2& pos):
Unit(pos), dx(0.f), dy(0.f)
{
}

DynamicUnit::DynamicUnit(const DynamicUnit& orig):
DynamicUnit(orig._pos)
{
}

DynamicUnit::~DynamicUnit() {
}

void DynamicUnit::Attack()
{
}
void DynamicUnit::WalkForward()
{
    dx = 0.1f;
}
void DynamicUnit::WalkBack()
{
    dx = -0.1f;
}
void DynamicUnit::Run()
{
}
void DynamicUnit::Jump()
{
    if(on_ground)
    {
        dy = -0.4;
        on_ground = false;
    }
}

void DynamicUnit::doUpdate(const UpdateState& us)
{
    _pos.x += dx * us.dt;

    // 0.0005f это ускорение
    if(!on_ground)
        dy = dy + 0.0005f * us.dt;

    _pos.y += dy * us.dt;

    on_ground = false;

    const spStage &st = getStage();
    const Vector2&sz = st->getSize();

    if(_pos.y > sz.y)
    {
        _pos.y = sz.y;
        dy = 0.f;
        on_ground = true;
    }

    Unit::doUpdate(us);
    dx = 0.f;
}
