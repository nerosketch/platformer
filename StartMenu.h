/* 
 * File:   StartMenu.h
 * Author: ns
 *
 * Created on October 24, 2018, 9:00 PM
 */

#ifndef STARTMENU_H
#define STARTMENU_H

#include "Menu.h"


DECLARE_SMART(StartMenu, spStartMenu);


class StartMenu : public Menu
{
private:
    INHERITED(Menu);
public:
    StartMenu();
    StartMenu(const StartMenu& orig);
    virtual ~StartMenu();

    // тут создаём следующий уровень и стаём зомби
    GameError make_next_level();

    void on_start_click(Event*);
    void on_exit_click(Event*);
};

#endif /* STARTMENU_H */

