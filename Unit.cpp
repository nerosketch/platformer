/* 
 * File:   Unit.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:45 AM
 */

#include "flags.h"
#include "Unit.h"


void InteractiveUnit::on_collideX(DynamicUnit *p_dunit, ITiledLevel *p_tl, const uint w)
{
    const float player_width = p_dunit->getWidth();
    const float tile_size_x = p_tl->getTileSize().x;

    if(p_dunit->dx > 0)
    {
        p_dunit->setX(w * tile_size_x - player_width);
        p_dunit->dx = -p_dunit->_tension;
    }
    else if(p_dunit->dx < 0)
    {
        p_dunit->setX(w * tile_size_x + tile_size_x);
        p_dunit->dx = p_dunit->_tension;
    }
}


void InteractiveUnit::on_collideY(DynamicUnit *p_dunit, ITiledLevel *p_tl, const uint h)
{
    const float player_height = p_dunit->getHeight();
    const float tile_size_y = p_tl->getTileSize().y;

    if(p_dunit->dy > 0)
    {
        p_dunit->setY(h * tile_size_y - player_height);
        p_dunit->dy = p_dunit->dx = 0.f;
        p_dunit->on_ground = true;
    }
    else if(p_dunit->dy < 0)
    {
        p_dunit->setY(h * tile_size_y + tile_size_y);
        p_dunit->dy = 0.f;
    }
}



UnitMap DynamicUnit::_map_interaction;


DynamicUnit::DynamicUnit(const Vector2& pos, ITiledLevel *level_ptr):
_speed(0.1f), _jump_speed(0.32f), _tension(0.05f), p_tiled_level(level_ptr),
dx(0.f), dy(0.f), on_ground(false)
{
#ifdef DBG
    logs::messageln("DynamicUnit:: ()");
#endif

    setPosition(pos);
}


DynamicUnit::DynamicUnit(const DynamicUnit& o):
DynamicUnit(o.getPosition(), o.p_tiled_level)
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



void DynamicUnit::_walkForward()
{
    dx = _speed;
}


void DynamicUnit::_walkBack()
{
    dx = -_speed;
}


void DynamicUnit::_jump()
{
    if(on_ground)
    {
        dy = -_jump_speed;
        on_ground = false;
    }
}


void DynamicUnit::doUpdate(const UpdateState& us)
{
    const Uint8 *p_date = SDL_GetKeyboardState(NULL);

    // ходим вправо
    if(p_date[SDL_GetScancodeFromKey(SDLK_d)])
    {
        if(isFlippedX())
            setFlippedX(false);

        _walkForward();
    }else
    // ходим влево
    if(p_date[SDL_GetScancodeFromKey(SDLK_a)])
    {
        if(!isFlippedX())
            setFlippedX(true);

        _walkBack();
    }

    if(p_date[SDL_GetScancodeFromKey(SDLK_w)] || p_date[SDL_GetScancodeFromKey(SDLK_SPACE)])
    {
        _jump();
    }

    /*
     * Применяем движение по ускорению dx dy,
     * и находим столкновения.
     */
    setX(getX() + dx * us.dt);

    // Обработка столкновений по x
    updateCollideX();

    if(!on_ground)
        dy = dy + p_tiled_level->getGravity() * us.dt;

    setY(getY() + dy * us.dt);

    on_ground = false;

    const float stage_height = getStage()->getHeight();

    // если упал вниз за пределы карты
    if(getY() >= stage_height)
    {
        setY(stage_height / 2.f);
        on_fall_down();
    }

    // Обработка столкновений по y
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
    {
        for(uint w = _pos.x / TILE_WIDTH; w < (_pos.x + sz.x) / TILE_WIDTH; w++)
        {
            InteractiveUnit *p_unit = _map_interaction[h][w];

            if(p_unit != nullptr)
            {
                p_unit->on_collideX(this, p_tiled_level, w);
                return;
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
    {
        for(uint w = _pos.x / TILE_WIDTH; w < (_pos.x + sz.x) / TILE_WIDTH; w++)
        {
            InteractiveUnit *p_unit = _map_interaction[h][w];
            if(p_unit != nullptr)
            {
                p_unit->on_collideY(this, p_tiled_level, h);
                return;
            }
        }
    }
}


void DynamicUnit::OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    switch(key_scancode)
    {
        case SDL_SCANCODE_D:
            WalkForward();
            break;
        case SDL_SCANCODE_A:
            WalkBack();
            break;
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_SPACE:
            Jump();
            break;
        default:
            Attack();
            break;
    }
}


void DynamicUnit::OnKeyUp(const SDL_KeyboardEvent&, const SDL_Scancode& key_scancode)
{
    if((key_scancode == SDL_Scancode::SDL_SCANCODE_D || key_scancode == SDL_Scancode::SDL_SCANCODE_A) && on_ground)
        dx = 0.f;
}
