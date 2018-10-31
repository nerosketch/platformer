/* 
 * File:   DebugRectSprite.cpp
 * Author: ns
 * 
 * Created on October 30, 2018, 4:48 PM
 */

#ifdef DBG
#include "DebugRectSprite.h"

DebugRectSprite::DebugRectSprite(const uint color, const Vector2 size)
{
    setSize(size);
    setColor(Color(color));
    setAlpha(80);
}


DebugRectSprite::DebugRectSprite(const DebugRectSprite& orig)
{
}

DebugRectSprite::~DebugRectSprite()
{
}

#endif
