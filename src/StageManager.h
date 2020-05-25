/* 
 * File:   StageManager.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:45 AM
 */

#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <list>
#include <oxygine-framework.h>
#include "GameStage.h"
#include "flags.h"
#include "base.h"


#ifdef DEBUG_DRAW_ENABLE
#include "base/Box2DDebugDraw.h"
#endif

#ifdef SOUND_ENABLE
#include "SoundManager.h"
#endif

using namespace std;
using namespace oxygine;


DECLARE_SMART(StageManager, spStageManager);

class StageManager : public Base, public Actor
{
private:
    INHERITED(Actor);
    StageManager();
    StageManager(const StageManager& orig);
    virtual ~StageManager();

    spGameStage current_stage;

#ifdef DEBUG_DRAW_ENABLE
    spBox2DDraw _debugDraw;
#endif
public:
    /*
     * Singleton of Meyers
     */
    static spStageManager getInstance()
    {
        #ifdef DBG
            logs::messageln("StageManager:: getInstance");
        #endif
        static spStageManager sp_st_mngr = new StageManager;
        return sp_st_mngr;
    }

    GameError init();

    void doUpdate(const UpdateState&);

#ifdef SOUND_ENABLE
    SoundManager *p_sound;
#endif

    // Если да то вышестоящий класс удалит нас
    bool is_zombie;
};

#endif /* STAGEMANAGER_H */

