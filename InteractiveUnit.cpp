/*
 * File:   InteractiveUnit.cpp
 * Author: ns
 *
 * Created on November 22, 2018, 8:35 PM
 */

#include "resources.h"
#include "InteractiveUnit.h"


InteractiveUnit::InteractiveUnit(const Vector2& pos) :
StaticUnit(pos)
{
    const ResAnim *p_res_anim = res::resources.getResAnim("pixeland");
    setResAnim(p_res_anim, 4, 66);
}

InteractiveUnit::InteractiveUnit(const InteractiveUnit& orig):
StaticUnit(orig)
{}

InteractiveUnit::~InteractiveUnit()
{}

void InteractiveUnit::on_collide(DynamicUnit* p_player)
{}

GameError InteractiveUnit::init()
{}
