/* 
 * File:   Enemy.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:08 AM
 */

#include "Enemy.h"

Enemy::Enemy(const Vector2& pos):
DynamicUnit(pos)
{
}

Enemy::Enemy(const Enemy& orig):
Enemy(orig.getPosition())
{
}

Enemy::~Enemy() {
}

