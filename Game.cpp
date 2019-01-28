/* 
 * File:   Game.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 10:53 AM
 */
#include <oxygine-framework.h>
#include "ResFontFT.h"

#include "flags.h"
#include "resources.h"
#include "Game.h"


#ifdef SOUND_ENABLE
#include <oxygine-sound.h>
#endif


using namespace oxygine;


Game::Game() :
    _viewport(Point(0, 0), core::getDisplaySize()),
    _clearColor(32, 32, 32, 255)
{}

Game::Game(const Game& o) :
    _viewport(o._viewport),
    _clearColor(o._clearColor)
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

    ResFontFT::initLibrary();

    auto p_stage = getStage();

    //spGamer gamer = new Gamer;
    //p_stage->addChild(gamer);

    stage_manager = StageManager::getInstance();
    GameError err = stage_manager->init();
    if(err != 0)
    {
        res::free();
        return err;
    }
    p_stage->addChild(stage_manager);


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

    ResFontFT::freeLibrary();

#ifdef SOUND_ENABLE
    stage_manager->p_sound->stop();

    SoundPlayer::free();
    SoundSystem::free();
#endif

    res::free();
}
bool Game::update()
{
    if(stage_manager->is_zombie)
    {
        auto p_stage = getStage();

        p_stage->removeChild(stage_manager);
        return true;
    }
    return false;
}
void Game::flush(){}
