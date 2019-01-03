/* 
 * File:   StartMenu.cpp
 * Author: ns
 * 
 * Created on October 24, 2018, 9:00 PM
 */

#include "flags.h"
#include "base.h"
#include "Btn.h"
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
    setResAnim(p_res_anim);

    const Vector2& im_size = p_res_anim->getSize();
    const Vector2& stage_size = getStage()->getSize();
    const Vector2 scale = CALC_SCALE(stage_size, im_size);
    setScale(scale);

    // звук навигации
    EventCallback ncb = CLOSURE(this, &StartMenu::on_mouse_over);

    // делаем кнопку start
    spBtn start_btn = new Btn("start_button");
    start_btn->setAnchor(0.5f, 0.5f);
    start_btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &StartMenu::on_start_click));
    start_btn->addEventListener(TouchEvent::OVER, ncb);
    Vector2 pos(455.5f, 128.f);
    start_btn->setPosition(pos);
    addChild(start_btn);

    // делаем кнопку exit
    spBtn exit_btn = new Btn("exit_button");
    exit_btn->setAnchor(0.5f, 0.5f);
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
