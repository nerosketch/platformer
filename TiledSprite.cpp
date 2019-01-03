/* 
 * File:   TiledSprite.cpp
 * Author: ns
 * 
 * Created on December 10, 2018, 12:01 AM
 */

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
        logs::error("Image not init");
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
    const float layer_height = _layer.options.height * _tile_size.y;
    const float& stage_height = getStage()->getHeight();
    setScale(stage_height / layer_height);

    nt = IVideoDriver::instance->createTexture();
    nt->init(im.lock());
    nt->setClamp2Edge(false);
    nt->setLinearFilter(false);

    _mat = new STDMaterial;
    _mat->_base = nt;
    _mat->_blend = blend_premultiplied_alpha;
}


TiledSprite::TiledSprite(const TiledSprite& orig)
{}


TiledSprite::~TiledSprite()
{}


void TiledSprite::_build_vert(vertexPCT2* p_verts, const Vector2& pos, const Point& res_coords)
{
    //const uint color = Color(Color::White).premultiplied().rgba();
    const uint color = 0xffffffff;

    float du = 1.f / (_sprite_size.x / _tile_size.x);
    float dv = 1.f / (_sprite_size.y / _tile_size.y);

    const float u = (_tile_size.x / _sprite_size.x) * res_coords.x;
    const float v = (_tile_size.y / _sprite_size.y) * res_coords.y;

    const Vector2& scale = getScale();

    vertexPCT2 *vt = &p_verts[0];
    vt->x = pos.x;
    vt->y = pos.y;
    vt->u = u;
    vt->v = v;
    vt->z = 0.f;
    vt->color = color;

    vt = &p_verts[1];
    vt->x = pos.x;
    vt->y = pos.y + _tile_size.y * scale.y;
    vt->u = u;
    vt->v = v + dv;
    vt->z = 0.f;
    vt->color = color;

    vt = &p_verts[2];
    vt->x = pos.x + _tile_size.x * scale.x;
    vt->y = pos.y;
    vt->u = u + du;
    vt->v = v;
    vt->z = 0.f;
    vt->color = color;

    vt = &p_verts[3];
    vt->x = pos.x + _tile_size.x * scale.x;
    vt->y = pos.y + _tile_size.y * scale.y;
    vt->u = u + du;
    vt->v = v + dv;
    vt->z = 0.f;
    vt->color = color;
}



void TiledSprite::doRender(const RenderState& rs)
{
    _mat->apply();

    STDRenderer* renderer = STDRenderer::getCurrent();
    renderer->setTransform(rs.transform);

    vertexPCT2 vert[4];

    uint block_index_counter = 0;
    Vector2 pos;
    const size_t vert_size = sizeof(vert);

    const Vector2& stage_size = getStage()->getSize();
    const Vector2 sprite_position = getAbsolutePosition();
    const Vector2& scale = getScale();

    const uint start_col = sprite_position.y / _tile_size.y;
    const uint end_col = (sprite_position.y + stage_size.y) / _tile_size.y;
    const uint start_row = sprite_position.x / _tile_size.x;
    const uint end_row = (sprite_position.x + stage_size.x) / _tile_size.x;

    for(uint col=0; col<_layer.options.height; col++)
    {
        if(col < start_col || col > end_col)
        {
            block_index_counter += _layer.options.width;
            continue;
        }

        for(uint row=0; row<_layer.options.width; row++)
        {
            if(row < start_row || row > end_row)
            {
                block_index_counter++;
                continue;
            }

            pos.x = row * _tile_size.x * scale.x;

            const uint block_id = _layer.int_data[block_index_counter++];

            if(block_id != 0)
            {
                const Point res_coords = _layer.get_coords_point(block_id);

                // Добавим блок
                //memset(vert, 0, vert_size);
                _build_vert(vert, pos + getParent()->getPosition() - getPosition(), res_coords);
                renderer->addVertices(vert, vert_size);
            }

        }

        pos.y = col * _tile_size.y * scale.y;
    }
}

Vector2 _get_absolute_pos(const Actor *p_actor, float x, float y)
{
    const Actor *p_parent_actor = p_actor->getParent();

    if(p_parent_actor == nullptr)
        return Vector2(x, y);

    x -= p_parent_actor->getX();
    y -= p_parent_actor->getY();
    return _get_absolute_pos(p_parent_actor, x, y);

}

Vector2 TiledSprite::getAbsolutePosition()
{
    return _get_absolute_pos(this, getX(), getY());
}






LAYER::LAYER()
{}

LAYER::LAYER(const LAYER& o) : options(o.options),
        int_data(o.int_data), tileheight(o.tileheight),
        p_tileset(o.p_tileset)
{
}

LAYER::~LAYER(){}


Point LAYER::get_coords_point(const uint block_index) const
{
    Point p;

    const uint row_len = p_tileset->columns;

    if(block_index == 0)
    {
        p.y = 0;
    }else
    {
        p.y = block_index / row_len;
        if(block_index % row_len == 0)
            p.y -= 1;
    }

    p.x = row_len - (((p.y+1) * row_len) - block_index) - 1;

    return p;
}


Vector2 LAYER::get_coords(const uint block_index) const
{
    Point p = get_coords_point(block_index);

    return Vector2(
        p.x * TILE_WIDTH,
        p.y * tileheight
    );
}
