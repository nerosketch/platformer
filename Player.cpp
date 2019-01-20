/* 
 * File:   Player.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:48 AM
 */
#include "flags.h"
#include "resources.h"
#ifdef DBG
#include "DebugRectSprite.h"
#endif
#include "Player.h"



Player::Player(const Vector2 &pos, ITiledLevel *p_level_ptr):
DynamicUnit(pos, p_level_ptr)
{
#ifdef DBG
    logs::messageln("Player::Player");
#endif

    p_res_anim = res::resources.getResAnim("character");
    setResAnim(p_res_anim);

    Idle();

    // Set scale
    //const Vector2& stage_size = getStage()->getScaledSize();
    //const Vector2 initial_scale = CALC_SCALE(stage_size, Vector2(INITIAL_STAGE_WIDTH, INITIAL_STAGE_HEIGHT));
    //setScale(initial_scale);

#ifdef DBG
    spDebugRectSprite ds(new DebugRectSprite(Color::Blue, getSize()));
    addChild(ds);
#endif
}


Player::Player(const Player& o):
Player(o.getPosition(), o.p_tiled_level)
{}


Player::~Player()
{}


void Player::OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
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
        case SDL_SCANCODE_F:
            Attack();
            break;
        default:
            break;
    }

    //DynamicUnit::OnKeyDown(ev, key_scancode);
}


void Player::OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    if((
            key_scancode == SDL_Scancode::SDL_SCANCODE_D ||
            key_scancode == SDL_Scancode::SDL_SCANCODE_A
    ) && current_tween)
    {
        current_tween->setLoops(1);
    }

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

        DynamicUnit::WalkForward();
    }else
    // ходим влево
    if(p_date[SDL_GetScancodeFromKey(SDLK_a)])
    {
        if(!isFlippedX())
            setFlippedX(true);

        DynamicUnit::WalkBack();
    }

    // прыгаем
    if(p_date[SDL_GetScancodeFromKey(SDLK_w)])
    {
        DynamicUnit::Jump();
    }

    DynamicUnit::doUpdate(us);
}


// Упал вниз карты
void Player::on_fall_down()
{
#ifdef DBG
    logs::messageln("Player::on_fall_down");
#endif
}



void Player::Attack()
{
    auto ta = Sprite::TweenAnim(p_res_anim, 3);
    ta.setInterval(0, 4);
    removeTween(current_tween);
    current_tween = addTween(ta, 500, 1);

    current_tween->setDoneCallback(CLOSURE(this, &Player::_on_tween_done));
}


void Player::WalkForward()
{
    if(isFlippedX())
        setFlippedX(false);

    Run();
}


void Player::WalkBack()
{
    if(!isFlippedX())
        setFlippedX(true);

    Run();
}


void Player::Run()
{
    removeTween(current_tween);
    current_tween = addTween(Sprite::TweenAnim(p_res_anim, 1), 500, -1);

    current_tween->setDoneCallback(CLOSURE(this, &Player::_on_tween_done));
}


void Player::Jump()
{
    auto ta = Sprite::TweenAnim(p_res_anim, 2);
    ta.setInterval(0, 3);
    removeTween(current_tween);
    current_tween = addTween(ta, 500, 1);

    current_tween->setDoneCallback(CLOSURE(this, &Player::_on_tween_done));
}


void Player::Idle()
{
    current_tween = addTween(Sprite::TweenAnim(p_res_anim, 0, 3), 500, -1);
}


void Player::_on_tween_done(Event*)
{
    Idle();
}
