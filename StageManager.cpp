/* 
 * File:   StageManager.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:45 AM
 */


#include "StageManager.h"


StageManager::StageManager()
{
#ifdef DBG
    logs::messageln("StageManager:: constructor");
#endif
}

StageManager::StageManager(const StageManager& orig) {
}

StageManager::~StageManager() {
}

GameError StageManager::init()
{
    auto stage = getStage();
    // set size of this object to size of the window
    setSize(stage->getSize());


#ifdef DEBUG_DRAW_ENABLE
    //Debug color box
    _debugDraw = new Box2DDraw;
    _debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
    _debugDraw->attachTo(this);
    _debugDraw->setWorld(SCALE);
    _debugDraw->setPriority(1);
#endif

    // Create stage instance
    spGameStage p_gstage = new GameStage();

    GameError err = p_gstage->load_stage("res/map.json");
    if(err != 0)
    {
        return err;
    }
    addChild(p_gstage);

    // Start music
#ifdef SOUND_ENABLE
    sound.startBackground();
#endif
    return GameError();
}

void StageManager::doUpdate(const UpdateState&)
{
#ifdef SOUND_ENABLE
    sound.doUpdate();
#endif
}
