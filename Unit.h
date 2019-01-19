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

    virtual void on_collideX(DynamicUnit*, const uint w);
    virtual void on_collideY(DynamicUnit*, const uint h);
};


class DynamicUnit : public Sprite, public InputEvent
{
private:
    friend class InteractiveUnit;

    Vector2 _tile_size;             // Размер одного блока карты
    float _speed;                   // Скорость равномерного передвижения
    float _jump_speed;              // Ускорение для прыжка
    float _tension;                 // Упругость, отскакивание от вертикальных поверхностей
    float _gravity;                 // Ускорение падения

    // карта для взаимодействий
    vector<vector<InteractiveUnit*>> _map_interaction;

    // Обработка столкновений
    void updateCollideX();
    void updateCollideY();

protected:
    // ускорение
    float dx, dy;
    // флаг, находимся-ли на земле
    bool on_ground;

    // упал в конец(низ) карты
    virtual void on_fall_down() = 0;

public:
    DynamicUnit(const Vector2& pos, const Vector2& tile_size);
    DynamicUnit(const DynamicUnit&);
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

    inline const Vector2& getTileSize() const { return _tile_size; }

    inline void setTileSize(const Vector2& o)
    {
        setTileSize(o.x, o.y);
    }

    inline void setTileSize(const float x, const float y)
    {
        _tile_size.x = x;
        _tile_size.y = y;
    }
};



#endif /* UNIT_H */
