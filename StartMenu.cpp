/* 
 * File:   StartMenu.cpp
 * Author: ns
 * 
 * Created on October 24, 2018, 9:00 PM
 */

#include <iostream>
#include "Btn.h"
#include "Level.h"
#include "StartMenu.h"


using namespace std;


StartMenu::StartMenu()
{
    spBtn btn = new Btn();
    addEventListener(TouchEvent::CLICK, CLOSURE(this, &StartMenu::on_click));
    Vector2 pos(80.f, 80.f);
    btn->setPosition(pos);

    addChild(btn);

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

    // если true то удаляем этот уровень и выполняем next_level
    is_zombie = true;
    
    return GameError();
}


void StartMenu::on_click(Event* ev)
{
#ifdef DBG
    cout << "StartMenu::on_click" << endl;
#endif
    GameError err = make_next_level();
    if(err != 0)
    {
        // произошла ошибка, убиваемся
        is_zombie = true;
        cout << "ERROR: StartMenu::on_click " << err.error_text << endl;
    }

}
