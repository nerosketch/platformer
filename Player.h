/* 
 * File:   Player.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:48 AM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <oxygine-framework.h>
#ifdef SOUND_ENABLE
#include "SoundManager.h"
#endif
#include "Unit.h"


using namespace oxygine;

DECLARE_SMART(Player, spPlayer);


class Player : public DynamicUnit
{
private:
    spTween current_tween;
    ResAnim *p_res_anim;

    void _on_tween_done(Event*);

public:
    Player(const Vector2 &pos, const Vector2& tile_size);
    Player(const Player&);
    virtual ~Player();

    //GameError init() override;

    void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;

    void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;

    void doUpdate(const UpdateState& us) override;

    void on_fall_down() override;

    virtual void Attack() override;
    virtual void WalkForward() override;
    virtual void WalkBack() override;
    virtual void Run() override;
    virtual void Jump() override;
    virtual void Idle();
};

#endif /* PLAYER_H */

