/* 
 * File:   Stage.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:42 AM
 */

#ifndef STAGE_H
#define STAGE_H

#include <oxygine-framework.h>
#include <vector>


#include "flags.h"
#include "Player.h"
#include "base.h"

#ifdef DEBUG_DRAW_ENABLE
#include "base/Box2DDebugDraw.h"
#endif

#ifdef SOUND_ENABLE
#include "SoundManager.h"
#endif


using namespace std;
using namespace oxygine;


DECLARE_SMART(GameStage, spGameStage);


class GameStage : public Base, public Actor
{
private:
    INHERITED(Actor);

    vector<Unit> units;
    spPlayer player;
    GameStage *p_next_stage;
    GameStage *p_prev_stage;

public:
    GameStage();
    GameStage(const GameStage& orig);
    virtual ~GameStage();

    GameError load_stage(string fname);
    
    void SwitchStage(spGameStage next_stage);
    
    void Pause();
    
    void Exit();
    
    //void doUpdate(const UpdateState& us) override;

};

#endif /* STAGE_H */

