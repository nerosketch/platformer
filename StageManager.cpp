/* 
 * File:   StageManager.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:45 AM
 */

//#include <algorithm>
#include "StartMenu.h"
#include "StageManager.h"


StageManager::StageManager() : is_zombie(false)
{
#ifdef DBG
    logs::messageln("StageManager:: constructor");
#endif

#ifdef SOUND_ENABLE
    SoundManager &sm = SoundManager::get_instance();
    p_sound = &sm;
#endif
}

StageManager::StageManager(const StageManager& orig)
{
}

StageManager::~StageManager()
{
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
    /*spGameStage p_gstage = new GameStage();

    GameError err = p_gstage->load_stage("res/map.json");
    if(err != 0)
    {
        return err;
    }
    append_stage(p_gstage);*/


    spStartMenu stage_menu = new StartMenu;
    current_stage = stage_menu;
    addChild(stage_menu);

    // Добавляем уровень интерфейса
    /*spGameStage stage = new GameStage;
    append_stage(stage);*/


    // Start music
#ifdef SOUND_ENABLE
    p_sound->startBackground();
#endif
    return GameError();
}

void StageManager::doUpdate(const UpdateState&)
{

    if(current_stage->is_zombie)
    {
        #ifdef DBG
            logs::messageln("StageManager:: doUpdate is_zombie");
        #endif
        /*
         * Проверяем стал ли текущий уровень зомби, если стал то нас
         * удалят и запустят новый уровень
         */
        spGameStage next_stage = current_stage->next_level;
        if(next_stage)
        {
            addChild(next_stage);
            removeChild(current_stage);
            current_stage = next_stage;
        }else
        {
            removeChild(current_stage);

            /*
             * Это был последний уровень, StageManager больше не нужен
             * и нас удалит вышестоящий уровень
             */
            is_zombie = true;
        }
    }
#ifdef SOUND_ENABLE
    p_sound->doUpdate();
#endif
}
