/* 
 * File:   Menu.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:44 AM
 */

#ifndef MENU_H
#define MENU_H

#include "GameStage.h"

class Menu : public GameStage
{
public:
    Menu();
    Menu(const Menu& orig);
    virtual ~Menu();
};

#endif /* MENU_H */

