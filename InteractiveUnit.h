/* 
 * File:   InteractiveUnit.h
 * Author: ns
 *
 * Created on November 22, 2018, 8:35 PM
 */

#ifndef INTERACTIVEUNIT_H
#define INTERACTIVEUNIT_H

#include <oxygine-framework.h>
#include "base.h"
#include "Unit.h"


using namespace oxygine;

DECLARE_SMART(InteractiveUnit, spInteractiveUnit);


class InteractiveUnit : public StaticUnit
{
public:
    InteractiveUnit(const Vector2& pos);
    InteractiveUnit(const InteractiveUnit& orig);
    virtual ~InteractiveUnit();

    //GameError init() override;
    void on_collide(DynamicUnit*) override;
};

#endif /* INTERACTIVEUNIT_H */
