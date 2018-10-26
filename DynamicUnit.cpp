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
Unit(pos), dx(0.f), dy(0.f), map_height(0), map_width(0), on_ground(false)
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

    // Обработка столкновений
    updateCollide();

    Unit::doUpdate(us);
}


void DynamicUnit::updateCollide()
{
    /*
     * Обработка столкновений
     * FIXME: БАЖНО РАБОТАЕТ СТОЛКНОВЕНИЕ ПО X
     */
    const Vector2 &sz = getSize();

    const vector<vector<uint>> &map = _map_interaction;

    for(uint h=_pos.y/32; h<(_pos.y+sz.y)/32; h++)
        for(uint w=_pos.x/32; w<(_pos.x+sz.x)/32; w++)
        {
            if(map[h][w] != 0)
            {
                if(dx != 0.f || dy != 0.f)
                    on_collide();

                if(dx > 0.f)
                {
                    _pos.x = w * 32 - sz.x;
                    dx = 0.f;
                }
                else if(dx < 0.f)
                {
                    _pos.x = w * 32 + 32.f;
                    dx = 0.f;
                }

                if(dy > 0.f)
                {
                    _pos.y = h * 32 - sz.y;
                    on_ground = true;
                    dy = 0.f;
                }
                else if(dy < 0.f)
                {
                    _pos.y = h * 32 + 32;
                    dy = 0.f;
                }
            }
        }
}


void DynamicUnit::SetMapInteraction(const vector<vector<uint>> &map)
{
    _map_interaction = map;
    map_height = map.size();
    map_width = map[0].size();
}


/*void DynamicUnit::OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    
}*/

void DynamicUnit::OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    if((key_scancode == SDL_Scancode::SDL_SCANCODE_D || key_scancode == SDL_Scancode::SDL_SCANCODE_A) && on_ground)
        dx = 0.f;
}
