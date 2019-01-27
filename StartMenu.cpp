/* 
 * File:   StartMenu.cpp
 * Author: ns
 * 
 * Created on October 24, 2018, 9:00 PM
 */

#include "flags.h"
#include "base.h"
#include "TextButton.h"
#include "Level.h"
#include "resources.h"
#include "StartMenu.h"

#ifdef SOUND_ENABLE
#include "SoundManager.h"
#endif


using namespace std;


StartMenu::StartMenu()
{
    const ResAnim *p_res_anim = res::resources.getResAnim("background");
    background_image->setResAnim(p_res_anim);
    background_image->setManageResAnim(true);

    //logs::messageln("scale %f", )
    setScale(getStage()->getHeight() / p_res_anim->getHeight());

    // звук навигации
    EventCallback ncb = CLOSURE(this, &StartMenu::on_mouse_over);

    const ResAnim *p_res_btn = res::resources.getResAnim("button");
    
    // делаем кнопку start
    spTextButton start_btn = new TextButton("Start");
    start_btn->setManageResAnim(true);
    start_btn->setAnchor(0.5f, 0.5f);
    start_btn->setScale(3.f);
    start_btn->setResAnim(p_res_btn);
    start_btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &StartMenu::on_start_click));
    start_btn->addEventListener(TouchEvent::OVER, ncb);
    Vector2 pos(455.5f, 128.f);
    start_btn->setPosition(pos);
    addChild(start_btn);

    // делаем кнопку exit
    spTextButton exit_btn = new TextButton("Exit");
    exit_btn->setManageResAnim(true);
    exit_btn->setAnchor(0.5f, 0.5f);
    exit_btn->setScale(3.f);
    exit_btn->setResAnim(p_res_btn);
    exit_btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &StartMenu::on_exit_click));
    exit_btn->addEventListener(TouchEvent::OVER, ncb);
    pos.y += 54;
    exit_btn->setPosition(pos);

    addChild(exit_btn);

#ifdef DBG
    logs::messageln("StartMenu::StartMenu");
#endif
}


StartMenu::StartMenu(const StartMenu& orig)
{
}


StartMenu::~StartMenu()
{
#ifdef DBG
    logs::messageln("StartMenu::StartMenu ~");
#endif
}

/*
 * Создаём следующий уровень, который последует за этим
 */
GameError StartMenu::make_next_level()
{
    spLevel _next_level = new Level;
    _next_level->init();
    next_level = _next_level;
    GameError err = _next_level->load_stage("res/map.json");
    if(err != 0)
    {
        return err;
    }

    Exit();

    return GameError();
}


void StartMenu::on_start_click(Event*)
{
#ifdef DBG
    logs::messageln("StartMenu::on_start_click");
#endif
    GameError err = make_next_level();
    if(err != 0)
    {
        // произошла ошибка, убиваемся
        Exit();
        logs::error("ERROR: StartMenu::on_start_click %s", err.error_text);
    }
}
void StartMenu::on_exit_click(Event*)
{
#ifdef DBG
    logs::messageln("StartMenu::on_exit_click");
#endif
    // завершаемся
    Exit();
}

void StartMenu::on_mouse_over(Event*)
{
#ifdef SOUND_ENABLE
    SoundManager &sm = SoundManager::get_instance();
    sm.menu_nav();
#endif
}
