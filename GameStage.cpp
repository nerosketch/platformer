/* 
 * File:   Stage.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:42 AM
 */

#include "GameStage.h"


#ifdef DBG
#include <iostream>
#endif



GameStage::GameStage():
is_zombie(false)
{
#ifdef DBG
    cout << "GameStage::GameStage" << endl;
#endif
}

GameStage::GameStage(const GameStage& orig)
{
#ifdef DBG
    cout << "GameStage::GameStage Copy" << endl;
#endif
}

GameStage::~GameStage()
{
#ifdef DBG
    cout << "GameStage:: ~" << endl;
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
