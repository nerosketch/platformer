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


using namespace std;
using namespace oxygine;


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


DECLARE_SMART(TILESET, spTILESET);

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


DECLARE_SMART(TiledSprite, spTiledSprite);

class TiledSprite : public Sprite
{
private:
    INHERITED(Sprite);
    void _build_vert(vertexPCT2* p_verts, const Vector2& pos, const Point& uv);

    spNativeTexture nt;

    LAYER _layer;
    Point _tile_size;
    Vector2 _sprite_size;

    void _init_mat(Image&);

public:
    TiledSprite(const LAYER&, string);
    TiledSprite(const LAYER&, Image&);
    TiledSprite(const TiledSprite& orig);
    virtual ~TiledSprite();

    void doRender(const RenderState&) override;
};

#endif /* TILEDSPRITE_H */

