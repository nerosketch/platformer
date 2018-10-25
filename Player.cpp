/* 
 * File:   Player.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:48 AM
 */
#include "resources.h"
#include "Player.h"


#ifdef DBG
#include <iostream>
using namespace std;
#endif


Player::Player(const Vector2 &pos):
DynamicUnit(pos)
{
    setAnchor(0.5f, 0.86f);
}

Player::Player(const Player& orig):
Player(orig._pos)
{
}

Player::~Player()
{
}

GameError Player::init()
{
    setResAnim(res::resources.getResAnim("anim_m"));

    return GameError();
}


void Player::OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    /*if(key_scancode == SDL_SCANCODE_D)
    {
        _pos.x += 15.f;
    }else if(key_scancode == SDL_SCANCODE_A)
        _pos.x -= 15.f;*/
}

void Player::OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
}


void Player::doUpdate(const UpdateState& us)
{
    const Uint8 *p_date = SDL_GetKeyboardState(NULL);

    // ходим вправо
    if(p_date[SDL_GetScancodeFromKey(SDLK_d)])
    {
        dx = 0.1f;
    }else
    // ходим влево
    if(p_date[SDL_GetScancodeFromKey(SDLK_a)])
    {
        dx = -0.1f;
    }

    // прыгаем
    if(p_date[SDL_GetScancodeFromKey(SDLK_w)])
    {
        if(on_ground)
        {
            dy = -0.4;
            on_ground = false;
        }
    }

    DynamicUnit::doUpdate(us);
}
