/* 
 * File:   TiledSprite.h
 * Author: ns
 *
 * Created on December 10, 2018, 12:01 AM
 */

#ifndef TILEDSPRITE_H
#define TILEDSPRITE_H

#include <string>
#include <oxygine-framework.h>
#include "flags.h"
#include "Unit.h"


using namespace std;
using namespace oxygine;


DECLARE_SMART(TILESET, spTILESET);
DECLARE_SMART(TiledSprite, spTiledSprite);
DECLARE_SMART(InteractiveTiledSprite, spInteractiveTiledSprite);


struct LAYER_OPTIONS
{
    uint width;
    uint height;
    float opacity;
    bool visible;
    float x;
    float y;
    short z_order;
    //string name;
};


class TILESET : public Object
{
    INHERITED(Object);
public:
    TILESET();
    TILESET(const TILESET&);
    virtual ~TILESET();

    uint firstgid;
    uint columns;
    string image;
    string name;
    uint imageheight;
    uint imagewidth;
    uint tilecount;
    uint tileheight;
    uint tilewidth;
};


class LAYER
{
public:
    LAYER();
    LAYER(const LAYER&);
    virtual ~LAYER();

    struct LAYER_OPTIONS options;
    vector<uint> int_data;
    uint tileheight;

    Point get_coords(const uint block_index) const;

    spTILESET p_tileset;

};



class TiledSprite : public Sprite
{
private:
    INHERITED(Sprite);
    void _build_vert(vertexPCT2* p_verts, const Vector2& pos, const Point& uv);

protected:
    spNativeTexture nt;

    LAYER _layer;
    Point _tile_size;
    Vector2 _sprite_size;

    void _init_mat(Image&);

public:
    TiledSprite(const LAYER&, const string&);
    TiledSprite(const LAYER&, Image&);
    TiledSprite(const TiledSprite& orig);
    virtual ~TiledSprite();

    void doRender(const RenderState&) override;
    Vector2 getAbsolutePosition();
};






class InteractiveTiledSprite : public TiledSprite, public InteractiveUnit
{
private:
    INHERITED(TiledSprite);

public:
    InteractiveTiledSprite(const LAYER&, const string&);
    InteractiveTiledSprite(const LAYER&, Image&);
    InteractiveTiledSprite(const InteractiveTiledSprite& orig);
    virtual ~InteractiveTiledSprite();

    //virtual void on_collide(DynamicUnit*);
};



#endif /* TILEDSPRITE_H */
