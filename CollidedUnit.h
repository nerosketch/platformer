/* 
 * File:   CollidedUnit.h
 * Author: ns
 *
 * Created on October 23, 2018, 7:50 PM
 */

#ifndef COLLIDEDUNIT_H
#define COLLIDEDUNIT_H

#include <memory>
#include <oxygine-framework.h>

#include "Unit.h"


using namespace std;
using namespace oxygine;


DECLARE_SMART(CollidedUnit, spCollidedUnit);


class CollidedUnit :public StaticUnit
{
public:
    CollidedUnit(const Vector2& pos, const ResAnim *p_res_anim, const shared_ptr<Point> res_coords);
    CollidedUnit(const Vector2& pos, const ResAnim *p_res_anim, int res_col, int res_row);
    CollidedUnit(const CollidedUnit& orig);
    virtual ~CollidedUnit();

    GameError init() override;

    void on_collide(DynamicUnit*) override;

};

#endif /* COLLIDEDUNIT_H */

