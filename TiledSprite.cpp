/* 
 * File:   TiledSprite.cpp
 * Author: ns
 * 
 * Created on December 10, 2018, 12:01 AM
 */

#include <iostream>
#include "TiledSprite.h"


TiledSprite::TiledSprite(const LAYER& lay, const string& texture_fname) :
_layer(lay), _tile_size(TILE_WIDTH, TILE_HEIGHT), _sprite_size(640.f, 1456.f)
{
    Image src;
    file::buffer fb;
    //load image from file

    file::read(texture_fname, fb);
    if(!src.init(fb, true))
    {
        cout << "Image not init" << endl;
        return;
    }

    _init_mat(src);
}


TiledSprite::TiledSprite(const LAYER& lay, Image& im) :
_layer(lay), _tile_size(TILE_WIDTH, TILE_HEIGHT), _sprite_size(640.f, 1456.f)
{
    _init_mat(im);
}

void TiledSprite::_init_mat(Image& im)
{
    nt = IVideoDriver::instance->createTexture();
    nt->init(im.lock());
    nt->setClamp2Edge(true);
    nt->setLinearFilter(false);

    _mat = new STDMaterial;
    _mat->_base = nt;
    _mat->_blend = blend_premultiplied_alpha;
}


TiledSprite::TiledSprite(const TiledSprite& orig)
{
}


TiledSprite::~TiledSprite()
{
}



void TiledSprite::_build_vert(vertexPCT2* p_verts, const Vector2& pos, const Point& res_coords)
{
    //const uint color = Color(Color::White).premultiplied().rgba();
    const uint color = 0xffffffff;

    //const Vector2 sprite_size(640.f, 1456.f);// = getSize();

    // Zero ???
    // cout << "Width " << getWidth() << endl;

    float du = 1.f / (_sprite_size.x / _tile_size.x);
    float dv = 1.f / (_sprite_size.y / _tile_size.y);

    const float u = (_tile_size.x / _sprite_size.x) * res_coords.x;
    const float v = (_tile_size.y / _sprite_size.y) * res_coords.y;

    vertexPCT2 *vt = &p_verts[0];
    vt->x = pos.x;
    vt->y = pos.y;
    vt->u = u;
    vt->v = v;
    vt->z = 0.f;
    vt->color = color;

    vt = &p_verts[1];
    vt->x = pos.x;
    vt->y = pos.y + _tile_size.y;
    vt->u = u;
    vt->v = v + dv;
    vt->z = 0.f;
    vt->color = color;

    vt = &p_verts[2];
    vt->x = pos.x + _tile_size.y;
    vt->y = pos.y;
    vt->u = u + du;
    vt->v = v;
    vt->z = 0.f;
    vt->color = color;

    vt = &p_verts[3];
    vt->x = pos.x + _tile_size.y;
    vt->y = pos.y + _tile_size.y;
    vt->u = u + du;
    vt->v = v + dv;
    vt->z = 0.f;
    vt->color = color;
}



void TiledSprite::doRender(const RenderState& rs)
{
    //Sprite::doRender(rs);
    _mat->apply();


    STDRenderer* renderer = STDRenderer::getCurrent();
    renderer->setTransform(rs.transform);

    //Transform world = rs.transform;
    //world.invert();

    //find top left local position of TiledActor visible on display
    //Vector2 topLeft = world.transform(Vector2(0, 0));

    //find bottom right local position of TiledActor visible on display
    //Vector2 bottomRight = world.transform(getStage()->getSize());

    //cout << "layers.size() " << layers.size() << endl;
//    for (std::list<layer>::const_iterator i = layers.begin(); i != layers.end(); ++i)
//        drawLayer(*i);


    //drawLayer();

    //float tw = TILE_WIDTH;//1.0f / nt->getWidth();
    //float th = TILE_HEIGHT;//1.0f / nt->getHeight();

    vertexPCT2 vert[4];

    uint block_index_counter = 0;
    Vector2 pos;
    size_t vert_size = sizeof(vert);

    for(uint col=0; col<_layer.options.height; col++)
    {
        for(uint row=0; row<_layer.options.width; row++)
        {
            pos.x = row * _tile_size.x;

            const uint block_id = _layer.int_data[block_index_counter++];

            if(block_id != 0)
            {
                const Point res_coords = _layer.get_coords(block_id);

                // Добавим блок
                //memset(vert, 0, vert_size);
                _build_vert(vert, pos + getParent()->getPosition() - getPosition(), res_coords);
                renderer->addVertices(vert, vert_size);
            }

        }
        pos.y = col * TILE_HEIGHT;

    }
}






InteractiveTiledSprite::InteractiveTiledSprite(const LAYER& lay, const string& tileset_fname) :
TiledSprite(lay, tileset_fname)
{
}

InteractiveTiledSprite::InteractiveTiledSprite(const LAYER& lay, Image& im) :
TiledSprite(lay, im)
{
}

InteractiveTiledSprite::InteractiveTiledSprite(const InteractiveTiledSprite& orig) :
TiledSprite(orig._layer, orig.nt->getName())
{
}

InteractiveTiledSprite::~InteractiveTiledSprite()
{
}

/*void InteractiveTiledSprite::on_collide(DynamicUnit* du)
{
    cout << "InteractiveTiledSprite::on_collide" << endl;
}*/
