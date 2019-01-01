/* 
 * File:   Unit.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:45 AM
 */

#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <oxygine-framework.h>
#include "InputEvent.h"


using namespace oxygine;
using namespace std;


class DynamicUnit;

class InteractiveUnit
{
public:
    InteractiveUnit(){};
    InteractiveUnit(const InteractiveUnit&){};
    virtual ~InteractiveUnit(){};

    virtual void on_collide(DynamicUnit*){};
};


class DynamicUnit : public Sprite, public InputEvent
{
private:
    float health;
    float damage;
    float weigth;
    uint lives;
    float speed;
    Point respawn_position;

    // карта для взаимодействий
    vector<vector<InteractiveUnit*>> _map_interaction;

    // Обработка столкновений
    void updateCollideX();
    void updateCollideY();

protected:
    float dx, dy;
    bool on_ground;

    // упал в конец(низ) карты
    virtual void on_fall_down() = 0;

public:
    DynamicUnit(const Vector2& pos);
    DynamicUnit(const DynamicUnit& orig);
    virtual ~DynamicUnit();

    virtual void Attack();
    virtual void WalkForward();
    virtual void WalkBack();
    virtual void Run();
    virtual void Jump();

    void doUpdate(const UpdateState& us) override;

    void SetMapInteraction(const vector<vector<InteractiveUnit*>>&);

    //ширина и высота карты
    uint map_width;
    uint map_height;

    //void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;

    void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
};



#endif /* UNIT_H */
