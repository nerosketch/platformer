/* 
 * File:   Landscape.cpp
 * Author: ns
 * 
 * Created on November 8, 2018, 9:39 PM
 */

#include <iostream>
#include "Landscape.h"


using namespace std;



Landscape::Landscape(const LAYER& lay, const ResAnim *p_res_anim):
tile_size(16, 16)
{
    data = lay.int_data;

    file::buffer fb;
    string texture("res/img/pixeland.png");
    //load image from file
    Image src;
    file::read(texture, fb);
    if(!src.init(fb, true))
    {
        cout << "Image not init" << endl;
        return;
    }
    cout << "Image: w " << src.getWidth() << " h " << src.getHeight() << " f " << src.getFormat() << endl;

    createTileSetTexture(src);


    /*uint block_index_counter = 0;
    Vector2 pos;
    const Vector2 block_size(TILE_WIDTH, TILE_HEIGHT);

    for(uint col=0; col<lay.options.height; col++)
    {
        for(uint row=0; row<lay.options.width; row++)
        {

            pos.x = row * TILE_WIDTH;

            const uint block_id = lay.int_data[block_index_counter++];

            if(block_id != 0)
            {
                const Point res_coords = lay.get_coords(block_id);

                // Добавим блок
                spSprite block = new Sprite;
                block->setSize(block_size);
                block->setPosition(pos);
                block->setResAnim(p_res_anim, res_coords.x, res_coords.y);
                addChild(block);
            }

        }
        pos.y = col * TILE_HEIGHT;

    }*/
}

Landscape::Landscape(const Landscape& orig)
{
}

Landscape::~Landscape()
{
}


void Landscape::createTileSetTexture(Image& src)
{
    cols = src.getWidth() / tile_size.x;
    rows = src.getHeight() / tile_size.y;

    /*Image dest;
    dest.init(cols * (tileWidth + 2), rows * (tileHeight * 2), TF_R8G8B8A8);

    cout << "Name " << dest.getName() << endl;

    //http://stackoverflow.com/questions/19611745/opengl-black-lines-in-between-tiles
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            Rect srcRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
            Rect destRect = srcRect;
            destRect.pos.x += 2 * x + 1;
            destRect.pos.y += 2 * y + 1;

            ImageData srcIm = src.lock(srcRect);
            ImageData destIm = dest.lock(destRect);
            operations::blit(srcIm, destIm);

            destRect.expand(Point(1, 1), Point(1, 1));



            operations::blit(
                dest.lock(destRect.pos.x + 1, destRect.pos.y + 1, tileWidth, 1),
                dest.lock(destRect.pos.x + 1, destRect.pos.y, tileWidth, 1));

            operations::blit(
                dest.lock(destRect.pos.x + 1, destRect.pos.y + tileHeight, tileWidth, 1),
                dest.lock(destRect.pos.x + 1, destRect.pos.y + tileHeight + 1, tileWidth, 1));

            operations::blit(
                dest.lock(destRect.pos.x + 1, destRect.pos.y, 1, tileHeight + 2),
                dest.lock(destRect.pos.x, destRect.pos.y, 1, tileHeight + 2));

            operations::blit(
                dest.lock(destRect.pos.x + tileWidth, destRect.pos.y, 1, tileHeight + 2),
                dest.lock(destRect.pos.x + tileWidth + 1, destRect.pos.y, 1, tileHeight + 2));

        }
    }*/


    nt = IVideoDriver::instance->createTexture();
    nt->init(src.lock());
    nt->setClamp2Edge(true);
    nt->setLinearFilter(false);



    mat = new STDMaterial;
    mat->_base = nt;
    mat->_blend = blend_premultiplied_alpha;
}


void Landscape::build_vert(vertexPCT2* p_verts, const Vector2& pos, const Point& res_coords)
{
    Color color(Color::White);

    vertexPCT2 vt;
    vt.color = color.premultiplied().rgba();

    const Vector2 sprite_size(640.f, 1456.f);// = getSize();

    // Zero ???
    // cout << "Width " << getWidth() << endl;

    /*
    Vector2 p1(pos.x, pos.y);
    Vector2 p2(pos.x, pos.y + tile_size.y);
    Vector2 p3(pos.x + tile_size.y, pos.y);
    Vector2 p4(pos.x + tile_size.y, pos.y + tile_size.y);*/

    float du = 0.025f;
    float dv = 0.025f;

    const float u = (tile_size.x / sprite_size.x) * res_coords.x;
    const float v = (tile_size.y / sprite_size.y) * res_coords.y;

    vt.z = 0;

    vt.x = pos.x;
    vt.y = pos.y;
    vt.u = u;
    vt.v = v;
    p_verts[0] = vt;

    vt.x = pos.x;
    vt.y = pos.y + tile_size.y;
    vt.u = u;
    vt.v = v + dv;
    p_verts[1] = vt;

    vt.x = pos.x + tile_size.y;
    vt.y = pos.y;
    vt.u = u + du;
    vt.v = v;
    p_verts[2] = vt;

    vt.x = pos.x + tile_size.y;
    vt.y = pos.y + tile_size.y;
    vt.u = u + du;
    vt.v = v + dv;
    p_verts[3] = vt;
}


void Landscape::drawLayer()
{
    /*int startX = 0;
    int startY = 0;
    int endX = 45;
    int endY = 31;
    width = 128;
    cols = rows = 16;

    const std::vector<uint>& tiles = data;*/

    Color color(Color::White);

    STDRenderer* renderer = STDRenderer::getCurrent();

    //float tw = TILE_WIDTH;//1.0f / nt->getWidth();
    //float th = TILE_HEIGHT;//1.0f / nt->getHeight();

    //cout << "startY " << startY << " endY " << endY << " tiles " << tiles.size() << endl;

    //for (int y = startY; y < endY; ++y)
    //{
        //for (int x = startX; x < endX; ++x)
        //{
            //cout << "y * width + x " << y * width + x << endl;
            //cout << " x " << x << " y " << y << " width " << width << " tw th" << tw << " " << th << endl;
            //uint tile = tiles[y * width + x];
            //cout << " tile " << tile << " cols " << cols << endl;
            //if (!tile)
            //    continue;
//
//            tile = tile - 1;
//
//            //cout << "col " << tile % cols << " row " << tile / cols << endl;
//
//            int col = 0;//tile % cols;
//            int row = 0;//tile / cols;
//
//            //cout << "col " << col << " row " << row << endl;
//
//            Rect src(col * (tileWidth + 2) + 1, row * (tileHeight + 2) + 1, tileWidth, tileHeight);
//
//            RectF srcUV = src.cast<RectF>();
//            srcUV.pos.x *= tw;
//            srcUV.pos.y *= th;
//            srcUV.size.x *= tw;
//            srcUV.size.y *= th;
//
//            Rect dest(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
//            RectF destF = dest.cast<RectF>();

            //cout << "x * tileWidth " << x * tileWidth << " y * tileHeight " << y * tileHeight << endl;

            //based on fillQuadT
            //unsigned int rgba = color.premultiplied().rgba();
//            const RectF& srcRect = srcUV;
//            const RectF& destRect = destF;

            //float u = srcRect.pos.x;
            //float v = srcRect.pos.y;
            //float u = 0.f;//srcRect.pos.x;
            //float v = 0.f;//srcRect.pos.y;

            //float du;// = srcRect.size.x;
            //float dv;// = srcRect.size.y;

            vertexPCT2 vert[4];
            
            build_vert(vert, Vector2(0.f, 0.f), Point(0, 0));
            renderer->addVertices(vert, sizeof(vert));

            //static float u = 0.f;
            //u += 0.001f;
            //cout << "U " << u << endl;
            build_vert(vert, Vector2(16.f, 0.f), Point(4, 0));
            renderer->addVertices(vert, sizeof(vert));


            /*cout << "Vert0 x " << vert[0].x << " y " << vert[0].y << " u " << vert[0].u << " v " << vert[0].v << endl;
            cout << "Vert1 x " << vert[1].x << " y " << vert[1].y << " u " << vert[1].u << " v " << vert[1].v << endl;
            cout << "Vert2 x " << vert[2].x << " y " << vert[2].y << " u " << vert[2].u << " v " << vert[2].v << endl;
            cout << "Vert3 x " << vert[3].x << " y " << vert[3].y << " u " << vert[3].u << " v " << vert[3].v << endl;*/
            //renderer->addVertices(vert, sizeof(vert));
        //}
    //}
    //cout << "end" << endl;
}


void Landscape::doRender(const RenderState& rs)
{
    mat->apply();


    STDRenderer* renderer = STDRenderer::getCurrent();
    renderer->setTransform(rs.transform);

    Transform world = rs.transform;
    world.invert();

    //find top left local position of TiledActor visible on display
    //Vector2 topLeft = world.transform(Vector2(0, 0));

    //find bottom right local position of TiledActor visible on display
    //Vector2 bottomRight = world.transform(getStage()->getSize());

    //cout << "layers.size() " << layers.size() << endl;
//    for (std::list<layer>::const_iterator i = layers.begin(); i != layers.end(); ++i)
//        drawLayer(*i);
    drawLayer();
}
