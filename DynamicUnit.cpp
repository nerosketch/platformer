/* 
 * File:   DynamicUnit.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:47 AM
 */

#include "flags.h"
#include "DynamicUnit.h"


#ifdef DBG
#include <iostream>
#endif


DynamicUnit::DynamicUnit(const Vector2& pos):
Unit(pos), dx(0.f), dy(0.f), map_height(0), map_width(0), on_ground(false)
{
}

DynamicUnit::DynamicUnit(const DynamicUnit& orig):
DynamicUnit(orig.getPosition())
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
    setX(getX() + dx * us.dt);
    updateCollideX();

    // 0.0005f это ускорение
    if(!on_ground)
        dy = dy + 0.0005f * us.dt;

    setY(getY() + dy * us.dt);

    on_ground = false;
    if(getY() >= 470.f)
    {
        setY(400.f);
        on_fall_down();
    }

    // Обработка столкновений
    updateCollideY();
}


void DynamicUnit::updateCollideX()
{
    /*
     * Обработка столкновений по x
     */
    const Vector2 &sz = getSize();
    const Vector2 &_pos = getPosition();
    const vector<vector<uint>> &map = _map_interaction;
    for(uint h = _pos.y / TILE_HEIGHT; h < (_pos.y + sz.y) / TILE_HEIGHT; h++)
        for(uint w = _pos.x / TILE_WIDTH; w < (_pos.x + sz.x) / TILE_WIDTH; w++)
        {
            if(map[h][w] != 0)
            {
                if(dx > 0)
                {
                    setX(w * TILE_WIDTH - sz.x);
                    on_collide();
                }
                if(dx < 0)
                {
                    setX(w * TILE_WIDTH + TILE_WIDTH);
                    on_collide();
                }
            }
        }
}

void DynamicUnit::updateCollideY()
{
    /*
     * Обработка столкновений по y
     */
    const Vector2 &sz = getSize();
    const Vector2 &_pos = getPosition();
    const vector<vector<uint>> &map = _map_interaction;
    for(uint h = _pos.y / TILE_HEIGHT; h < (_pos.y + sz.y) / TILE_HEIGHT; h++)
        for(uint w = _pos.x / TILE_WIDTH; w < (_pos.x + sz.x) / TILE_WIDTH; w++)
        {
            if(map[h][w] != 0)
            {
                if(dy>0)
                {
                    setY(h * TILE_HEIGHT - sz.y);
                    dy = dx = 0.f;
                    on_ground = true;
                }
                else if(dy<0)
                {
                    setY(h * TILE_HEIGHT + TILE_HEIGHT);
                    dy = 0.f;
                    on_collide();
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
