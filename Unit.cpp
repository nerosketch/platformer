/* 
 * File:   Unit.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:45 AM
 */

#include "flags.h"
#include "Unit.h"


DynamicUnit::DynamicUnit(const Vector2& pos, const Vector2& tile_size):
_tile_size(tile_size), _speed(0.1f), _jump_speed(0.4f),
_tension(0.05f), _gravity(0.0005f),
dx(0.f), dy(0.f), on_ground(false)
{
    setPosition(pos);
    setTileSize(tile_size);
}


DynamicUnit::DynamicUnit(const DynamicUnit& o):
DynamicUnit(o.getPosition(), o.getTileSize())
{}


DynamicUnit::~DynamicUnit()
{}


void DynamicUnit::Attack()
{
}


void DynamicUnit::WalkForward()
{
    dx = _speed;
}


void DynamicUnit::WalkBack()
{
    dx = -_speed;
}


void DynamicUnit::Run()
{
}


void DynamicUnit::Jump()
{
    if(on_ground)
    {
        dy = -_jump_speed;
        on_ground = false;
    }
}


void DynamicUnit::doUpdate(const UpdateState& us)
{
    setX(getX() + dx * us.dt);
    updateCollideX();

    // 0.0005f это ускорение
    if(!on_ground)
        dy = dy + _gravity * us.dt;

    setY(getY() + dy * us.dt);

    on_ground = false;

    const float stage_height = getStage()->getHeight();

    if(getY() >= stage_height)
    {
        setY(stage_height / 2.f);
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
    for(uint h = _pos.y / TILE_HEIGHT; h < (_pos.y + sz.y) / TILE_HEIGHT; h++)
        for(uint w = _pos.x / TILE_WIDTH; w < (_pos.x + sz.x) / TILE_WIDTH; w++)
        {
            InteractiveUnit *p_unit = _map_interaction[h][w];
            if(p_unit != nullptr)
            {
                if(dx > 0)
                {
                    setX(w * _tile_size.x - sz.x);
                    dx = -_tension;
                    p_unit->on_collide(this);
                }
                else if(dx < 0)
                {
                    setX(w * _tile_size.x + _tile_size.x);
                    dx = _tension;
                    p_unit->on_collide(this);
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
    for(uint h = _pos.y / TILE_HEIGHT; h < (_pos.y + sz.y) / TILE_HEIGHT; h++)
        for(uint w = _pos.x / TILE_WIDTH; w < (_pos.x + sz.x) / TILE_WIDTH; w++)
        {
            InteractiveUnit *p_unit = _map_interaction[h][w];
            if(p_unit != nullptr)
            {
                if(dy > 0)
                {
                    setY(h * _tile_size.y - sz.y);
                    dy = dx = 0.f;
                    on_ground = true;
                    p_unit->on_collide(this);
                }
                else if(dy < 0)
                {
                    setY(h * _tile_size.y + _tile_size.y);
                    dy = 0.f;
                    p_unit->on_collide(this);
                }
            }
        }
}


void DynamicUnit::SetMapInteraction(const vector<vector<InteractiveUnit*>> &map)
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
