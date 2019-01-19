/* 
 * File:   Unit.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:45 AM
 */

#include "flags.h"
#include "Unit.h"


void InteractiveUnit::on_collideX(DynamicUnit *p_dunit, const uint w)
{
    const Vector2 &sz = p_dunit->getSize();

    if(p_dunit->dx > 0)
    {
        p_dunit->setX(w * p_dunit->_tile_size.x - sz.x);
        p_dunit->dx = -p_dunit->_tension;
    }
    else if(p_dunit->dx < 0)
    {
        p_dunit->setX(w * p_dunit->_tile_size.x + p_dunit->_tile_size.x);
        p_dunit->dx = p_dunit->_tension;
    }
}


void InteractiveUnit::on_collideY(DynamicUnit *p_dunit, const uint h)
{
    const Vector2 &sz = p_dunit->getSize();

    if(p_dunit->dy > 0)
    {
        p_dunit->setY(h * p_dunit->_tile_size.y - sz.y);
        p_dunit->dy = p_dunit->dx = 0.f;
        p_dunit->on_ground = true;
    }
    else if(p_dunit->dy < 0)
    {
        p_dunit->setY(h * p_dunit->_tile_size.y + p_dunit->_tile_size.y);
        p_dunit->dy = 0.f;
    }
}




DynamicUnit::DynamicUnit(const Vector2& pos, const Vector2& tile_size):
_tile_size(tile_size), _speed(0.1f), _jump_speed(0.4f),
_tension(0.05f), _gravity(0.0005f),
dx(0.f), dy(0.f), on_ground(false)
{
#ifdef DBG
    logs::messageln("DynamicUnit:: ()");
#endif

    setPosition(pos);
    setTileSize(tile_size);
}


DynamicUnit::DynamicUnit(const DynamicUnit& o):
DynamicUnit(o.getPosition(), o.getTileSize())
{
#ifdef DBG
    logs::messageln("DynamicUnit:: Copy");
#endif
}


DynamicUnit::~DynamicUnit()
{
#ifdef DBG
    logs::messageln("DynamicUnit:: ~");
#endif
}


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
                p_unit->on_collideX(this, w);
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
                p_unit->on_collideY(this, h);
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
