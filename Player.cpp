/* 
 * File:   Player.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:48 AM
 */
#include "flags.h"
#include "resources.h"
#include "DebugRectSprite.h"
#include "Player.h"


#ifdef DBG
#include <iostream>
using namespace std;
#endif


Player::Player(const Vector2 &pos):
DynamicUnit(pos)
{
    setResAnim(res::resources.getResAnim("anim_m"));
    //setAnchor(0.f, 0.f);

/*#ifdef DBG
    // тестовая кнопка
    spDebugRectSprite sprite = new DebugRectSprite(Color::Magenta, Vector2(25.f, 44.f));
    addChild(sprite);
#endif*/
}

Player::Player(const Player& orig):
Player(orig.getPosition())
{
}

Player::~Player()
{
}

/*GameError Player::init()
{
    return GameError();
}*/


void Player::OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    if(key_scancode == SDL_SCANCODE_D || key_scancode == SDL_SCANCODE_A)
    {
        current_tween = addTween(Sprite::TweenAnim(getResAnim()), 500, -1);
    }

    //DynamicUnit::OnKeyDown(ev, key_scancode);
}

void Player::OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    if((key_scancode == SDL_Scancode::SDL_SCANCODE_D || key_scancode == SDL_Scancode::SDL_SCANCODE_A) && current_tween)
        removeTween(current_tween);

    DynamicUnit::OnKeyUp(ev, key_scancode);
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


// Упал вниз карты
void Player::on_fall_down()
{
#ifdef DBG
    cout << "Player::on_fall_down" << endl;
#endif
}
