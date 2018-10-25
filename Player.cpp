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
    if(key_scancode == SDL_SCANCODE_D || key_scancode == SDL_SCANCODE_A)
    {
        current_tween = addTween(Sprite::TweenAnim(getResAnim()), 500, -1);
    }/*else if(key_scancode == SDL_SCANCODE_A)
        _pos.x -= 15.f;*/
}

void Player::OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    if(current_tween)
        removeTween(current_tween);
}


void Player::doUpdate(const UpdateState& us)
{
    const Uint8 *p_date = SDL_GetKeyboardState(NULL);

    // ходим вправо
    if(p_date[SDL_GetScancodeFromKey(SDLK_d)])
    {
        if(isFlippedX())
            setFlippedX(false);

        WalkForward();
    }else
    // ходим влево
    if(p_date[SDL_GetScancodeFromKey(SDLK_a)])
    {
        if(!isFlippedX())
            setFlippedX(true);

        WalkBack();
    }

    // прыгаем
    if(p_date[SDL_GetScancodeFromKey(SDLK_w)])
    {
        Jump();
    }

    DynamicUnit::doUpdate(us);
}
