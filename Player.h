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
#include "TiledLevel.h"


using namespace oxygine;

DECLARE_SMART(Player, spPlayer);


class Player : public DynamicUnit
{
private:
    spTween current_tween;
    ResAnim *p_res_anim;

    void _on_tween_done(Event*);

public:
    Player(const Vector2 &pos, ITiledLevel*);
    Player(const Player&);
    virtual ~Player();

    //GameError init() override;

    void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;

    void on_fall_down() override;

    void Attack() final override;
    void WalkForward() final override;
    void WalkBack() final override;
    void Run();
    void Jump() final override;
    void Idle();
};

#endif /* PLAYER_H */

