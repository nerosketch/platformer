/* 
 * File:   DebugRectSprite.h
 * Author: ns
 *
 * Created on October 30, 2018, 4:48 PM
 */

#ifdef DBG
#ifndef DEBUGRECTSPRITE_H
#define DEBUGRECTSPRITE_H

#include <oxygine-framework.h>

using namespace oxygine;


DECLARE_SMART(DebugRectSprite, spDebugRectSprite);


class DebugRectSprite : public ColorRectSprite
{
private:
    INHERITED(ColorRectSprite);
public:
    DebugRectSprite(const uint, const Vector2 size);
    DebugRectSprite(const DebugRectSprite&);
    virtual ~DebugRectSprite();

};

#endif
#endif /* DEBUGRECTSPRITE_H */

