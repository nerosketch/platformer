/* 
 * File:   Stage.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:42 AM
 */

#include "GameStage.h"


GameStage::GameStage():
is_zombie(false)
{
#ifdef DBG
    logs::messageln("GameStage::GameStage");
#endif
}

GameStage::GameStage(const GameStage& orig)
{
#ifdef DBG
    logs::messageln("GameStage::GameStage Copy");
#endif
}

GameStage::~GameStage()
{
#ifdef DBG
    logs::messageln("GameStage:: ~");
#endif
}


void GameStage::Pause()
{
}

void GameStage::Exit()
{
    is_zombie = true;
}


/*void GameStage::doUpdate(const UpdateState& us)
{
}*/
