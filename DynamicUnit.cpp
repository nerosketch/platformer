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

    setPosition(_pos);
}


void DynamicUnit::updateCollide()
{
    /*
     * Обработка столкновений
     * FIXME: БАЖНО РАБОТАЕТ СТОЛКНОВЕНИЕ ПО X
     */
    const Vector2 &sz = getSize();

    const vector<vector<uint>> &map = _map_interaction;

    for(uint h=_pos.y/TILE_HEIGHT; h<(_pos.y+sz.y)/TILE_HEIGHT; h++)
        for(uint w=_pos.x/TILE_WIDTH; w<(_pos.x+sz.x)/TILE_WIDTH; w++)
        {
            if(map[h][w] != 0)
            {
                if(dx != 0.f || dy != 0.f)
                    on_collide();

                // Если двигаемся вправо
                if(dx > 0.f)
                {
                    // получаем правую точку
                    const float right_point = _pos.x + sz.x;

                    // получаем координату левого ребра блока который
                    // находится под этой точкой
                    const uint right_block_coord_x = static_cast<uint>(right_point / TILE_WIDTH);

                    // Если эта координата текущая
                    if(right_block_coord_x == w)
                    {
                        // тогда устанавливаем левую координату персонажа
                        // в координату этого ребра
                        _pos.x = right_block_coord_x * TILE_WIDTH;
                    }
                    // останавливаем персонажа
                    dx = 0.f;
                }
                // Если двигаемся влево
                else if(dx < 0.f)
                {
                    // находим левую точку блока персонажа
                    const uint left_block_coord_x = static_cast<uint>(_pos.x / TILE_WIDTH);

                    // если текущий блок это тот что под левой координатой
                    if(left_block_coord_x == w)
                    {
                        // тогда устанавливаем левую координату персонажа
                        // в правую координату блока
                        _pos.x = left_block_coord_x * TILE_WIDTH + TILE_WIDTH;
                    }

                    // останавливаем персонажа
                    dx = 0.f;
                }

                // Если двигаемся вниз
                if(dy > 0.f)
                {
                    // получаем нижнюю точку
                    const float bottom_point = _pos.y + sz.y;

                    // получаем координату нижнего ребра блока который
                    // находится под этой точкой
                    const uint bottom_block_coord_y = static_cast<uint>(bottom_point / TILE_HEIGHT);

                    // если это текущая координата
                    if(bottom_block_coord_y == h)
                    {
                        // Тогда устанавливаем верхнюю координату персонажа
                        // в верхнюю координату блока
                        _pos.y = bottom_block_coord_y * TILE_HEIGHT + TILE_HEIGHT;
                    }

                    // персонаж на земле
                    on_ground = true;
                    // останавливаем персонажа
                    dy = 0.f;
                }
                // двигаемся вверх (скорее всего прыгаем)
                else if(dy < 0.f)
                {
                    // получаем верхнюю точку блока персоажа
                    const uint top_block_coord_y = static_cast<uint>(_pos.y / TILE_HEIGHT);

                    // если текущий блок это тот что под верхней координатой
                    if(top_block_coord_y == h)
                    {
                        // тогда устанавливаем верхнюю координату персонажа
                        // в нижнюю координату блока
                        _pos.y = top_block_coord_y * TILE_HEIGHT + TILE_HEIGHT;
                    }

                    // останавливаем прыжок
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
