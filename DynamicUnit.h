/* 
 * File:   DynamicUnit.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:47 AM
 */

#ifndef DYNAMICUNIT_H
#define DYNAMICUNIT_H

#include <vector>
#include <oxygine-framework.h>
#include "Unit.h"

using namespace std;
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

    // карта для взаимодействий
    vector<vector<uint>> _map_interaction;

    // Обработка столкновений
    void updateCollideX();
    void updateCollideY();

protected:
    float dx, dy;
    bool on_ground;
    virtual void on_collide() = 0;

public:
    DynamicUnit(const Vector2& pos);
    DynamicUnit(const DynamicUnit& orig);
    virtual ~DynamicUnit();

    void Attack();
    void WalkForward();
    void WalkBack();
    void Run();
    void Jump();

    void doUpdate(const UpdateState& us) override;

    void SetMapInteraction(const vector<vector<uint>>&);

    //ширина и высота карты
    uint map_width, map_height;

    //void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;

    void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
};

#endif /* DYNAMICUNIT_H */
