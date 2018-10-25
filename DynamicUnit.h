/* 
 * File:   DynamicUnit.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:47 AM
 */

#ifndef DYNAMICUNIT_H
#define DYNAMICUNIT_H

#include <oxygine-framework.h>
#include "Unit.h"


using namespace oxygine;


class DynamicUnit : public Unit, public InputEvent
{
private:
    float health;
    float damage;
    float weigth;
    uint lives;
    float speed;
    Point respawn_position;

protected:
    float dx, dy;
    bool on_ground;

public:
    DynamicUnit(const Vector2& pos);
    DynamicUnit(const DynamicUnit& orig);
    virtual ~DynamicUnit();

    void Attack();
    void Walk(Vector2 &direction);
    void Run(Vector2 &direction);
    void Jump();

    void doUpdate(const UpdateState& us) override;
};

#endif /* DYNAMICUNIT_H */

