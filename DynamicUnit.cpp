/* 
 * File:   DynamicUnit.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:47 AM
 */

#include "DynamicUnit.h"

DynamicUnit::DynamicUnit(const Vector2& pos):
Unit(pos)
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
void DynamicUnit::Walk(Vector2 &direction)
{
}
void DynamicUnit::Run(Vector2 &direction)
{
}
void DynamicUnit::Jump()
{
}
