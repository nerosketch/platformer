/* 
 * File:   StaticUnit.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:46 AM
 */

#ifndef STATICUNIT_H
#define STATICUNIT_H

#include "Unit.h"


class StaticUnit : public Unit
{
public:
    StaticUnit(const Vector2& pos);
    StaticUnit(const StaticUnit& orig);
    virtual ~StaticUnit();
private:

};

#endif /* STATICUNIT_H */

