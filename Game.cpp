/* 
 * File:   Game.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 10:53 AM
 */
#include <oxygine-framework.h>

#include "flags.h"
#include "resources.h"
#include "StageManager.h"
#include "Game.h"


#ifdef SOUND_ENABLE
#include <oxygine-sound.h>
#endif


using namespace oxygine;


Game::Game()
{}

Game::Game(const Game& orig)
{}

Game::~Game()
{}


void Game::preinit(){}

GameError Game::init()
{
#ifdef DBG
    logs::messageln("Game:: init");
#endif

#ifdef SOUND_ENABLE
    SoundSystem::create()->init(16);
    SoundPlayer::initialize();
#endif

    res::load();

    auto p_stage = getStage();

    //spGamer gamer = new Gamer;
    //p_stage->addChild(gamer);

    /*spBtn btn = new Btn();
    btn->setPosition(512.0f, 64.0f);
    //and add it to Stage as child
    p_stage->addChild(btn);*/

    spStageManager smngr = StageManager::getInstance();
    GameError err = smngr->init();
    if(err != 0)
    {
        res::free();
        return err;
    }
    p_stage->addChild(smngr);


    // Слой интерфейса
    //spInterfaceStage p_int_stage = new InterfaceStage();
    //p_stage->addChild(p_int_stage);

    // Движение сцены
    /*Vector2 screen_size = p_stage->getSize();
    Vector2 dest = Vector2(screen_size.x, screen_size.y/2);
    
    spTweenQueue tq = new TweenQueue();
    tq->add(Sprite::TweenPosition(dest), 10000);
    //addTween(tq)->detachWhenDone(true);
    p_stage->addTween(tq);*/

    return GameError();
}
void Game::destroy()
{
    #ifdef DBG
        logs::messageln("Game:: destroy");
    #endif

#ifdef SOUND_ENABLE
    spWorld world = World::getInstance();
    world->sound.stop();
#endif

    res::free();

#ifdef SOUND_ENABLE
    SoundPlayer::free();
    SoundSystem::free();
#endif

}
void Game::update(){}
void Game::flush(){}
