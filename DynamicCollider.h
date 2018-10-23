/* 
 * File:   DynamicCollider.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:20 AM
 */

#ifndef DYNAMICCOLLIDER_H
#define DYNAMICCOLLIDER_H

#include "BaseCollider.h"


class DynamicCollider : public BaseCollider
{
public:
    DynamicCollider();
    DynamicCollider(const DynamicCollider& orig);
    virtual ~DynamicCollider();
private:

};

#endif /* DYNAMICCOLLIDER_H */

