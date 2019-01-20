/* 
 * File:   Menu.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:44 AM
 */

#include "Menu.h"


Menu::Menu() : background_image(new Sprite)
{
    addChild(background_image);
}


Menu::Menu(const Menu& o) : background_image(o.background_image)
{}


Menu::~Menu() {
}

