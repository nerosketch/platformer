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
#ifdef SOUND_ENABLE
#include "SoundManager.h"
#endif
#include "Player.h"



Player::Player(const Vector2 &pos, ITiledLevel *p_level_ptr):
DynamicUnit(pos, p_level_ptr)
{
#ifdef DBG
    logs::messageln("Player::Player");
#endif

    setResAnim(res::resources.getResAnim("character"));

    // Set scale
    //const Vector2& stage_size = getStage()->getScaledSize();
    //const Vector2 initial_scale = CALC_SCALE(stage_size, Vector2(INITIAL_STAGE_WIDTH, INITIAL_STAGE_HEIGHT));
    //setScale(initial_scale);

/*#ifdef DBG
    spDebugRectSprite ds(new DebugRectSprite(Color::Blue, getSize()));
    addChild(ds);
#endif*/
}


Player::Player(const Player& o):
Player(o.getPosition(), o.p_tiled_level)
{}


Player::~Player()
{}


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


// Упал вниз карты
void Player::on_fall_down()
{
#ifdef DBG
    logs::messageln("Player::on_fall_down");
#endif
}


void Player::Attack()
{
    if(_is_ignore_input)
        return;

    auto ta = Sprite::TweenAnim(getResAnim(), 3);
    ta.setInterval(0, 4);
    if(current_tween)
        removeTween(current_tween);
    current_tween = addTween(ta, 500, 1);

    current_tween->setDoneCallback(CLOSURE(this, &Player::_on_tween_done));

#ifdef SOUND_ENABLE
    SoundManager::get_instance().play_from_name("door-hit");
#endif
}


void Player::WalkForward()
{
    if(_is_ignore_input)
        return;

    if(isFlippedX())
        setFlippedX(false);

    Run();
}


void Player::WalkBack()
{
    if(_is_ignore_input)
        return;

    if(!isFlippedX())
        setFlippedX(true);

    Run();
}


void Player::Run()
{
    if(_is_ignore_input)
        return;

    if(current_tween)
        removeTween(current_tween);
    current_tween = addTween(Sprite::TweenAnim(getResAnim(), 1), 500, -1);

    current_tween->setDoneCallback(CLOSURE(this, &Player::_on_tween_done));
}


void Player::Jump()
{
#ifdef DBG
    logs::messageln("Player::Jump");
#endif

    if(_is_ignore_input)
        return;

    auto ta = Sprite::TweenAnim(getResAnim(), 2);
    ta.setInterval(0, 3);
    if(current_tween)
        removeTween(current_tween);
    current_tween = addTween(ta, 500, 1);

    current_tween->setDoneCallback(CLOSURE(this, &Player::_on_tween_done));
    
#ifdef SOUND_ENABLE
    SoundManager::get_instance().play_from_name("8-bit-jump");
#endif
}


void Player::Idle()
{
    if(_is_ignore_input)
        return;

    current_tween = addTween(Sprite::TweenAnim(getResAnim(), 0, 3), 500, -1);
}


void Player::_on_tween_done(Event*)
{
    Idle();
}


// Вызывается когда заканчивается прыжок
void Player::OnDismount()
{
    // Если кнопка бега всё ещё нажата то надо включить анимацию бега
    const Uint8 *p_date = SDL_GetKeyboardState(NULL);

    if((p_date[SDL_GetScancodeFromKey(SDLK_d)] || p_date[SDL_GetScancodeFromKey(SDLK_a)]) && on_ground)
        Run();
    else
        Idle();
}
