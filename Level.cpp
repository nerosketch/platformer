/* 
 * File:   Level.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:43 AM
 */
#include <iostream>
#include "resources.h"
#include "Level.h"



Level::Level()
{
#ifdef DBG
    cout << "Level::Level" << endl;
#endif
}

Level::Level(const Level& orig)
{
}

Level::~Level()
{
#ifdef DBG
    cout << "Level::Level ~" << endl;
#endif
}


/*
* Загружаем статичные блоки, с ними можно взаимодействовать
*/
void Level::_load_terrain(const vector<LAYER>& lays, Image& im)
{
    if(lays.size() < 1)
    {
        cerr << "ERROR: layers count less than one" << endl;
        return;
    }

    const uint layer_height = lays[0].options.height;

    // карта взаимодействий
    map_interaction.resize(layer_height);

    for(const LAYER& lay : lays)
    {
        uint block_index_counter = 0;

        spInteractiveTiledSprite terr_el(new InteractiveTiledSprite(lay, im));
        addChild(terr_el);

        for(uint col=0; col<lay.options.height; col++)
        {
            vector<InteractiveUnit*> &line = map_interaction[col];

            if(line.size() < lay.options.width)
                line.resize(lay.options.width);

            for(uint row=0; row<lay.options.width; row++)
            {
                const uint block_id = lay.int_data[block_index_counter++];

                if(block_id != 0)
                {
                    line[row] = static_cast<InteractiveUnit*>(terr_el.get());
                }

            }

        }
    }

    // Ставим сундуки для взаимодействий
    //spInteractiveUnit iu = new InteractiveUnit(Vector2(130.f, 330.f));
    //addChild(iu);

}


GameError Level::load_stage(const string fname)
{
    ObjectLoader ol;
    ol.open(fname);

    //const ResAnim *p_res_anim = res::resources.getResAnim("pixeland");
    Image src;
    file::buffer fb;
    //load image from file

    string tileset_fname("res/img/pixeland.png");
    file::read(tileset_fname, fb);
    if(!src.init(fb, true))
    {
        cout << "Image not init" << endl;
        return GameError(1, "Image not init");
    }

    // Загрузим пейзаж
    landscape = new TiledSprite(ol.landscape, src);
    addChild(landscape);

    // Загрузим фон
    for(LAYER &lay : ol.backgrounds)
    {
        spTiledSprite background = new TiledSprite(lay, src);
        addChild(background);
    }

    // Загрузим землю
    _load_terrain(ol.terrains, src);

    // установим факелы
    ResAnim *torch_res_anim = res::resources.getResAnim("torch_anim");
    Vector2 pos(0.f, 317.f);
    for(uint n=0; n < 7; n++)
    {
        pos.x = 350 + (112.f * n);

        // Загрузим анимированный факел
        spSprite block = new Sprite;
        //block->setSize(TILE_WIDTH, TILE_HEIGHT);
        block->setPosition(pos);
        block->setResAnim(torch_res_anim);
        block->addTween(Sprite::TweenAnim(getResAnim()), RANDOM_RANGE(400, 500), -1);
        addChild(block);
    }


    // Загрузим игрока
    pos.y = 160.f;
    pos.x = 80.f;
    player = new Player(pos);
    player->SetMapInteraction(map_interaction);
    addChild(player);

    return GameError();
}


/*
 * Скроллим карту
 */
void Level::doUpdate(const UpdateState& us)
{
    const float player_pos_x = player->getX();
    const spStage &stage = getStage();
    const float stage_half_width = stage->getWidth() / 2.f;

    if(player_pos_x > stage_half_width)
    {
        setX(stage_half_width - player_pos_x);
    }


    // Прокручиваем задний фон по медленнее
    landscape->setX(
        -(getX() / 2.f)
    );
}


void Level::OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    
}


void Level::OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    if(key_scancode == SDL_Scancode::SDL_SCANCODE_ESCAPE)
        is_zombie = true;
}
