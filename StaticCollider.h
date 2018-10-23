/* 
 * File:   StaticCollider.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:13 AM
 */

#ifndef STATICCOLLIDER_H
#define STATICCOLLIDER_H

#include "BaseCollider.h"


class StaticCollider : public BaseCollider
{
public:
    StaticCollider();
    StaticCollider(const StaticCollider& orig);
    virtual ~StaticCollider();
private:

};

#endif /* STATICCOLLIDER_H */

