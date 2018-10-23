/* 
 * File:   BaseSprite.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:42 AM
 */

#ifndef BASESPRITE_H
#define BASESPRITE_H

#include <oxygine-framework.h>
#include "InputEvent.h"


using namespace oxygine;


class BaseSprite : public InputEvent, public Sprite
{
    INHERITED(Sprite);
public:
    BaseSprite();
    BaseSprite(const BaseSprite& orig);
    virtual ~BaseSprite();
private:

};

#endif /* BASESPRITE_H */

