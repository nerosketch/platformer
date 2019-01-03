/* 
 * File:   DebugRectSprite.cpp
 * Author: ns
 * 
 * Created on October 30, 2018, 4:48 PM
 */

#ifdef DBG
#include "flags.h"
#include "DebugRectSprite.h"


DebugRectSprite::DebugRectSprite() : DebugRectSprite(Color::Blue, Vector2(TILE_WIDTH, TILE_HEIGHT))
{}


DebugRectSprite::DebugRectSprite(const uint color, const Vector2 size)
{
    setSize(size);
    setColor(Color(color));
    setAlpha(85);
}


DebugRectSprite::DebugRectSprite(const DebugRectSprite& orig)
{
}


DebugRectSprite::~DebugRectSprite()
{
}

#endif
