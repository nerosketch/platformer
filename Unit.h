/* 
 * File:   Unit.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:45 AM
 */

#ifndef UNIT_H
#define UNIT_H

#include <oxygine-framework.h>
#include "InputEvent.h"
#include "TiledLevel.h"


using namespace oxygine;


class DynamicUnit;

class InteractiveUnit
{
public:
    InteractiveUnit(){};
    InteractiveUnit(const InteractiveUnit&){};
    virtual ~InteractiveUnit(){};

    virtual void on_collideX(DynamicUnit*, ITiledLevel*, const uint w);
    virtual void on_collideY(DynamicUnit*, ITiledLevel*, const uint h);
};


typedef vector<vector<InteractiveUnit*>> UnitMap;


class DynamicUnit : public Sprite, public InputEvent
{
private:
    friend class InteractiveUnit;

    float _speed;                   // Скорость равномерного передвижения
    float _jump_speed;              // Ускорение для прыжка
    float _tension;                 // Упругость, отскакивание от вертикальных поверхностей

    // карта для взаимодействий
    static UnitMap _map_interaction;

    // Обработка столкновений
    void updateCollideX();
    void updateCollideY();

    void _jump();
    void _walkForward();
    void _walkBack();

    bool _dismount_flag;

protected:
    ITiledLevel *p_tiled_level;

    // упал в конец(низ) карты
    virtual void on_fall_down() = 0;

public:
    DynamicUnit(const Vector2& pos, ITiledLevel*);
    DynamicUnit(const DynamicUnit&);
    virtual ~DynamicUnit();

    // ускорение
    float dx, dy;
    // флаг, находимся-ли на земле
    bool on_ground;

    virtual void Attack() = 0;
    virtual void WalkForward() = 0;
    virtual void WalkBack() = 0;
    virtual void Jump() = 0;

    virtual void doUpdate(const UpdateState& us) override;

    // static const UnitMap& getMapInteraction() const {return _map_interaction; }
    static UnitMap& getMapInteraction() {return _map_interaction; }

    inline ITiledLevel* getTiledLevel(){ return p_tiled_level; }

    virtual void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
    virtual void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;

    // Вызывается когда заканчивается прыжок
    virtual void OnDismount() = 0;
};



#endif /* UNIT_H */
