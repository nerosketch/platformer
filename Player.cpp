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
}

Player::Player(const Player& orig):
Player(orig._pos)
{
    setAnchor(0.5f, 0.86f);
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
#ifdef DBG
    cout << "Player::OnKeyDown" << endl;
#endif
    if(key_scancode == SDL_SCANCODE_D)
    {
        _pos.x += 15.f;
    }else if(key_scancode == SDL_SCANCODE_A)
        _pos.x -= 15.f;
    setPosition(_pos);
}

void Player::OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
#ifdef DBG
    cout << "Player::OnKeyUp" << endl;
#endif
}
