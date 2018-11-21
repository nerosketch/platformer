/* 
 * File:   StartMenu.cpp
 * Author: ns
 * 
 * Created on October 24, 2018, 9:00 PM
 */

#include <iostream>
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

    setResAnim(res::resources.getResAnim("background"));

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


    /*tex = new TextPanel("npNbet. R npowy npoWehur 3a to 4to Aabho he nNwy.\n"
                        "HaAerC6 ha to 4to choba nozy4ntcr oBWatjcr...");
    tex->setPosition(130.f, 330.f);
    tex->addEventListener(TouchEvent::CLICK, CLOSURE(this, &StartMenu::on_panel_button_clicked));
    addChild(tex);*/

#ifdef DBG
    cout << "StartMenu::StartMenu" << endl;
#endif
}


StartMenu::StartMenu(const StartMenu& orig)
{
}


StartMenu::~StartMenu()
{
#ifdef DBG
    cout << "StartMenu::StartMenu ~" << endl;
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
    cout << "StartMenu::on_start_click" << endl;
#endif
    GameError err = make_next_level();
    if(err != 0)
    {
        // произошла ошибка, убиваемся
        Exit();
        cout << "ERROR: StartMenu::on_start_click " << err.error_text << endl;
    }
}
void StartMenu::on_exit_click(Event*)
{
#ifdef DBG
    cout << "StartMenu::on_exit_click" << endl;
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
