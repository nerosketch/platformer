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
#include "ObjectLoader.h"


using namespace std;
using namespace oxygine;


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

public:
    TiledSprite(const LAYER&, string texture_fname);
    TiledSprite(const TiledSprite& orig);
    virtual ~TiledSprite();

    void doRender(const RenderState&) override;
};

#endif /* TILEDSPRITE_H */

