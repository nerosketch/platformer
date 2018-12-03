/* 
 * File:   Landscape.h
 * Author: ns
 *
 * Created on November 8, 2018, 9:38 PM
 */

#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <oxygine-framework.h>
#include "flags.h"
#include "ObjectLoader.h"

using namespace oxygine;


DECLARE_SMART(Landscape, spLandscape);


class Landscape : public Sprite
{
private:
    INHERITED(Sprite);

    void build_vert(vertexPCT2* p_verts, const Vector2& pos, const Point& uv);

public:
    Landscape(const LAYER&, const ResAnim*);
    Landscape(const Landscape& orig);
    virtual ~Landscape();
    
    
    struct layer
    {
        vector<unsigned int> tiles;
    };

    list< layer > layers;


    int width;
    int height;

    spNativeTexture nt;
    spSTDMaterial mat;

    int cols;
    int rows;
    
    vector<uint> data;

    Point tile_size;

    void createTileSetTexture(Image&);
    void drawLayer();
    void doRender(const RenderState& rs) override;
};

#endif /* LANDSCAPE_H */
