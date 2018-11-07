/* 
 * File:   Level.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:43 AM
 */
#include <iostream>
#include "resources.h"
#include "CollidedUnit.h"
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
void Level::_load_terrain(const vector<LAYER>& lays, const ResAnim *p_res_anim)
{
    const Vector2 block_size(TILE_WIDTH, TILE_HEIGHT);

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
        Vector2 pos;

        for(uint col=0; col<lay.options.height; col++)
        {
            vector<uint> &line = map_interaction[col];

            if(line.size() < lay.options.width)
                line.resize(lay.options.width);

            for(uint row=0; row<lay.options.width; row++)
            {

                pos.x = row * TILE_WIDTH;

                const uint block_id = lay.int_data[block_index_counter++];

                if(block_id != 0)
                {
                    const shared_ptr<Point> res_coords = lay.get_coords(block_id);

                    // Добавим блок
                    spCollidedUnit block = new CollidedUnit(pos, p_res_anim, res_coords);
                    block->setSize(block_size);
                    //block->setPriority(lay.options.z_order);
                    addChild(block);

                    line[row] = block_id;
                }

            }
            pos.y = col * TILE_HEIGHT;

        }
    }

    /*Vector2 pos(0.f, 0.f);
    shared_ptr<Point> res_coords(new Point(0, 0));
    spCollidedUnit block = new CollidedUnit(pos, p_res_anim, res_coords);
    block->setSize(block_size);
    //block->setPriority(lay.options.z_order);
    addChild(block);*/
}


void Level::_load_background(LAYER& lay, const ResAnim *p_res_anim)
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
                const shared_ptr<Point> res_coords = lay.get_coords(block_id);

                // Добавим блок
                spSprite block = new Sprite;
                block->setSize(block_size);
                block->setPosition(pos);
                block->setResAnim(p_res_anim, res_coords->x, res_coords->y);
                addChild(block);
            }

        }
        pos.y = col * TILE_HEIGHT;

    }
}


GameError Level::load_stage(const string fname)
{
    background_image = new Sprite;
    background_image->setResAnim(res::resources.getResAnim("abckgroun"));
    addChild(background_image);

    ObjectLoader ol;
    ol.open(fname);

    const ResAnim *p_res_anim = res::resources.getResAnim("pixeland");

    // Загрузим фон
    for(LAYER &lay : ol.backgrounds)
        _load_background(lay, p_res_anim);

    // Загрузим землю
    _load_terrain(ol.terrains, p_res_anim);

    /*for(char& c : line)
    {
        switch(c)
        {
            case 'm':
            {
                spSquareBlockSprite block = new SquareBlockSprite(p_world, pos);
                p_stage->addChild(block);
                break;
            }
            case 'i':
            {
                player = new Gamer(p_world);
                GameError err = player->init(pos);
                if(err != 0)
                {
                    return err;
                }
                p_stage->addChild(player);
                break;
            }
            case 'e':
                spGamerEnemi p_enemy = new GamerEnemi(p_world);
                GameError err = p_enemy->init(pos);
                if(err != 0)
                {
                    return err;
                }
                //enemies[e_count++] = p_enemy;
                p_stage->addChild(p_enemy);
                break;
        }
        pos.x += 32.0f;
    }
    pos.x = 0;
    pos.y += 32.0f;
    }*/


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
    GameError err = player->init();
    if(err != 0)
    {
        return err;
    }
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
    background_image->setX(
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
