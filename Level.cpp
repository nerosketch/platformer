/* 
 * File:   Level.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 9:43 AM
 */
#include <vector>
#include "resources.h"
#include "flags.h"
#ifdef DBG
#include "DebugRectSprite.h"
#endif
#include "Level.h"


Level::Level() : _light_material(new LightMaterial)
{
#ifdef DBG
    logs::messageln("Level::Level");
#endif
}


Level::Level(const Level&)
{}


Level::~Level()
{
#ifdef DBG
    logs::messageln("Level::Level ~");
#endif
}


void Level::init()
{
    // Set scale
    const float stage_height = getStage()->getScaledHeight();
    setScale(stage_height / INITIAL_STAGE_HEIGHT);
}


/*
* Загружаем статичные блоки, с ними можно взаимодействовать
*/
void Level::_load_terrain(const LAYERS& lays, Image& im, const list<RectF>& objects)
{
    if(lays.size() < 1)
    {
        logs::error("ERROR: layers count less than one");
        return;
    }
    
    const uint layer_height = lays[0].options.height;
    RectF rect(0.f, 0.f, TILE_WIDTH, TILE_HEIGHT);

    // карта взаимодействий
    UnitMap& map_interaction = DynamicUnit::getMapInteraction();
    map_interaction.resize(layer_height);

    for(const LAYER& lay : lays)
    {
        uint block_index_counter = 0;

        spTiledSprite terr_el(new TiledSprite(lay, im));
        _light_material->applyMateralTo(terr_el.get());
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
                    rect.pos.y = col * TILE_WIDTH;
                    rect.pos.x = row * TILE_HEIGHT;

                    for(const RectF& r : objects)
                    {
                        if(r.isIntersecting(rect))
                            line[row] = &liu;
                        else
                        {
                            if(lay.layer_type == LayerType::BTERRAIN)
                            {
                                line[row] = &stairs;
                            }
                            else
                            {
                                line[row] = &empty_iu;
                            }
                        }
                    }
                }
            }
        }
    }
}


GameError Level::load_stage(const string& fname)
{
#ifdef DBG
    logs::messageln("Level::load_stage");
#endif

    ObjectLoader ol;
    ol.open(fname);

    //const ResAnim *p_res_anim = res::resources.getResAnim("pixeland");
    Image src;
    file::buffer fb;

    string tileset_fname("res/img/pixeland.png");
    file::read(tileset_fname, fb);
    if(!src.init(fb, true))
    {
        logs::error("Image not init");
        return GameError(1, "Image not init");
    }

    // Загрузим пейзаж
    landscape = new TiledSprite(ol.landscape, src);
    //_light_material->applyMateralTo(landscape.get());
    addChild(landscape);

    // Загрузим фон
    for(LAYER &lay : ol.backgrounds)
    {
        spTiledSprite background = new TiledSprite(lay, src);
        _light_material->applyMateralTo(background.get());
        addChild(background);
    }

    // Загрузим землю
    _load_terrain(ol.terrains, src, ol.objects);

    // установим факелы
    ResAnim *torch_res_anim = res::resources.getResAnim("torch_anim");
    Vector2 pos(0.f, 317.f);
    Vector4 light_color(1.f, 1.f, 1.f, 1.f);

    for(uint n=0; n < 7; n++)
    {
        pos.x = 350 + (112.f * n);

        // Загрузим анимированный факел
        spSprite block = new Sprite;
        //block->setSize(TILE_WIDTH, TILE_HEIGHT);
        block->setPosition(pos);
        block->addTween(Sprite::TweenAnim(torch_res_anim), RANDOM_RANGE(400, 500), -1);

        // Добавим источник света к факелу
        auto lp = new LightPoint(pos);
        lp->setIntense(2.f);
        lp->setLightColor(light_color);
        lp->setRadius(50.f);
        lp->attachTo(block);

        addChild(block);
    }

    // Загрузим игрока
    pos.y = 160.f;
    pos.x = 30.f;
    player = new Player(pos, this);
    const UnitMap& map_interaction = DynamicUnit::getMapInteraction();
    setMapSize(PointU(
        map_interaction[0].size(),
        map_interaction.size()
    ));
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
        (getX() / 4.f)
    );
}


void Level::OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{}


void Level::OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    if(key_scancode == SDL_Scancode::SDL_SCANCODE_ESCAPE)
        is_zombie = true;
}






void LevelInteractiveUnit::on_collideX(DynamicUnit* p_du, ITiledLevel *ptl, const uint w)
{
    InteractiveUnit::on_collideX(p_du, ptl, w);

    if(!_is_text_panel_exist)
    {
        spTextPanel tex(new TextPanel("Test text..."));
        tex->setPosition(26.f, -16.f);
        tex->setTimeToLive(3000);
        tex->setOnDieEvent(CLOSURE(this, &LevelInteractiveUnit::free_text_panel));
        _is_text_panel_exist = true;

        p_du->addChild(tex);
    }
}

void LevelInteractiveUnit::free_text_panel(Event*)
{
    _is_text_panel_exist = false;
}




void StairsInteractiveUnit::on_collideY(DynamicUnit *p_du, ITiledLevel *p_tl, const uint h)
{
    //InteractiveUnit::on_collideY(p_du, p_tl, h);

#ifdef DBG
    logs::messageln("StairsInteractiveUnit::on_collideY dy=%.2f", p_du->dy);
#endif

    const float player_height = p_du->getHeight();
    const float tile_size_y = p_tl->getTileSize().y;

    if(p_du->dy > 0)
    {
        p_du->setY(h * tile_size_y - player_height);
        p_du->dy = p_du->dx = 0.f;
        p_du->on_ground = true;
    }
    /*else if(p_du->dy < 0)
    {
        p_du->setY(h * tile_size_y + tile_size_y);
        p_du->dy = 0.f;
    }*/
}


void StairsInteractiveUnit::on_collideX(DynamicUnit*, ITiledLevel*, const uint)
{
    
}
