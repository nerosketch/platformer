/*
 * File:   InteractiveUnit.cpp
 * Author: ns
 *
 * Created on November 22, 2018, 8:35 PM
 */

#include "resources.h"
#include "InteractiveUnit.h"


#ifdef DBG
#include <iostream>
using namespace std;
#endif


InteractiveUnit::InteractiveUnit(const Vector2& pos) :
StaticUnit(pos)
{
    //const ResAnim *p_res_anim = res::resources.getResAnim("treasure");
    //setResAnim(p_res_anim);
}


InteractiveUnit::InteractiveUnit(const InteractiveUnit& orig):
StaticUnit(orig)
{}


InteractiveUnit::~InteractiveUnit()
{}


void InteractiveUnit::on_collide(DynamicUnit* p_player)
{
#ifdef DBG
    cout << "InteractiveUnit::on_collide" << endl;
#endif
}


/*GameError InteractiveUnit::init()
{
    return GameError();
}*/
