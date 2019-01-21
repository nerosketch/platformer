/* 
 * File:   Menu.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:44 AM
 */

#ifndef MENU_H
#define MENU_H

#include <oxygine-framework.h>
#include "GameStage.h"

using namespace oxygine;


class Menu : public GameStage
{
protected:
    spSprite background_image;

public:
    Menu();
    Menu(const Menu& orig);
    virtual ~Menu();
};

#endif /* MENU_H */

