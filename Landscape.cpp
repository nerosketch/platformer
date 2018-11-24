/* 
 * File:   Landscape.cpp
 * Author: ns
 * 
 * Created on November 8, 2018, 9:39 PM
 */

#include "Landscape.h"

Landscape::Landscape(const LAYER& lay, const ResAnim *p_res_anim)
{
    uint block_index_counter = 0;
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

    }
}

Landscape::Landscape(const Landscape& orig)
{
}

Landscape::~Landscape()
{
}
