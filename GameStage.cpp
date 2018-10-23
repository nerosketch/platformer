/* 
 * File:   Stage.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:42 AM
 */

#include "CollidedUnit.h"
#include "ObjectLoader.h"
#include "resources.h"
#include "GameStage.h"


#ifdef DBG
#include <iostream>
#endif



GameStage::GameStage()
{
#ifdef DBG
    cout << "GameStage::GameStage" << endl;
#endif
}

GameStage::GameStage(const GameStage& orig)
{
#ifdef DBG
    cout << "GameStage::GameStage Copy" << endl;
#endif
}

GameStage::~GameStage()
{
#ifdef DBG
    cout << "GameStage:: ~" << endl;
#endif
}


GameError GameStage::load_stage(string fname)
{
    Vector2 pos;
    //auto p_stage = getStage();

    ObjectLoader ol;
    ol.open(fname);

    const ResAnim *p_res_anim = res::resources.getResAnim("la");

    for( LAYER &lay : ol.layers )
    {
        uint block_index_counter = 0;

        for(uint col=0; col<lay.options.height; col++)
        {
            for(uint row=0; row<lay.options.width; row++)
            {

                pos.x = row * 32.f;

                const uint block_id = lay.int_data[block_index_counter++];

                if(block_id != 0)
                {
                    const shared_ptr<Point> res_coords = lay.get_coords(block_id);

                    // Добавим блок
                    spCollidedUnit block = new CollidedUnit(pos, p_res_anim, res_coords);
                    addChild(block);
                }
 
            }
            pos.y = col * 32.f;
        }

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
        pos.y += 32.0f;*/
    }

    // Загрузим игрока
    pos.x = 80.f;
    pos.y = 160.f;
    player = new Player(pos);
    GameError err = player->init();
    if(err != 0)
    {
        return err;
    }
    addChild(player);

    return GameError();
}


void GameStage::SwitchStage(spGameStage next_stage)
{
    
}

void GameStage::Pause()
{
    
}

void GameStage::Exit()
{
    
}


/*void GameStage::doUpdate(const UpdateState& us)
{}*/
