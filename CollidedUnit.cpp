/* 
 * File:   CollidedUnit.cpp
 * Author: ns
 * 
 * Created on October 23, 2018, 7:50 PM
 */

#include "flags.h"
#include "DebugRectSprite.h"
#include "CollidedUnit.h"


CollidedUnit::CollidedUnit(const Vector2& pos, const ResAnim *p_res_anim, const shared_ptr<Point> res_coords):
CollidedUnit(pos, p_res_anim, res_coords->x, res_coords->y)
{
}

CollidedUnit::CollidedUnit(const Vector2& pos, const ResAnim *p_res_anim, int res_col, int res_row):
StaticUnit(pos)
{
    setResAnim(p_res_anim, res_col, res_row);
    //setResAnim(p_res_anim, 6, 0);

    //setScale(2.f);
    //setAnchor(0.f, 0.f);

#ifdef DBG
    spDebugRectSprite sprite = new DebugRectSprite(Color::Blue, Vector2(TILE_WIDTH, TILE_HEIGHT));
    addChild(sprite);
#endif
}

CollidedUnit::CollidedUnit(const CollidedUnit& orig):
CollidedUnit(orig._pos, orig.getResAnim(), orig.getColumn(), orig.getRow())
{
}

CollidedUnit::~CollidedUnit()
{
}

GameError CollidedUnit::init()
{
    return GameError();
}
