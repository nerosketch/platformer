/* 
 * File:   Unit.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:45 AM
 */

#ifndef UNIT_H
#define UNIT_H

#include <oxygine-framework.h>
#include "InputEvent.h"

using namespace oxygine;

class Unit : public Sprite
{
public:
    Unit(const Vector2& pos);
    Unit(const Unit& orig);
    virtual ~Unit();

    virtual GameError init() = 0;
};

#endif /* UNIT_H */
