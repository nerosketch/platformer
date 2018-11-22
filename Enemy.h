/* 
 * File:   Enemy.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:08 AM
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "Unit.h"


class Enemy : public DynamicUnit
{
public:
    Enemy(const Vector2& pos);
    Enemy(const Enemy& orig);
    virtual ~Enemy();
private:

};

#endif /* ENEMY_H */

