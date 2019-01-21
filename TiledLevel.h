/* 
 * File:   TiledLevel.h
 * Author: bashmak
 *
 * Created on 19 января 2019 г., 22:35
 */

#ifndef TILEDLEVEL_H
#define TILEDLEVEL_H

#include <vector>
#include <oxygine-framework.h>
#include "GameStage.h"
#include "InputEvent.h"

using namespace oxygine;
using namespace std;


typedef VectorT2<uint> PointU;



class ITiledLevel : public GameStage, public InputEvent
{
protected:
    //ширина и высота карты
    PointU _map_size;

    // Размер одного блока карты
    Vector2 _tile_size;

    // Ускорение падения
    float gravity;

public:
    ITiledLevel();
    ITiledLevel(const ITiledLevel&);
    virtual ~ITiledLevel();

    virtual void init() = 0;

    inline const Vector2& getTileSize() const { return _tile_size; }

    inline void setTileSize(const Vector2& o) { setTileSize(o.x, o.y); }

    inline void setTileSize(const float x, const float y)
    {
        _tile_size.x = x;
        _tile_size.y = y;
    }

    inline void setMapSize(const PointU& sz) { _map_size = sz; }
    inline const PointU& getMapSize() const { return _map_size; }

    inline void setGravity(const float g){ gravity = g; }
    inline const float getGravity() const {return gravity; }
};

#endif /* TILEDLEVEL_H */

