/* 
 * File:   Stage.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:42 AM
 */

#ifndef STAGE_H
#define STAGE_H

#include <oxygine-framework.h>



#include "flags.h"
#include "Player.h"
#include "base.h"

#ifdef DEBUG_DRAW_ENABLE
#include "base/Box2DDebugDraw.h"
#endif

#ifdef SOUND_ENABLE
#include "SoundManager.h"
#endif


using namespace oxygine;


DECLARE_SMART(GameStage, spGameStage);


class GameStage : public Base, public Actor
{
private:
    INHERITED(Actor);


public:
    GameStage();
    GameStage(const GameStage& orig);
    virtual ~GameStage();

    bool is_zombie;

    

    void Pause();

    void Exit();

    //void doUpdate(const UpdateState& us) override;


    // Тут появится следующий уровень после смерти текущего уровня.
    // т.е. когда is_zombie станет true
    spGameStage next_level;
};

#endif /* STAGE_H */

