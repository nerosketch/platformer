/* 
 * File:   Level.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:43 AM
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <oxygine-framework.h>
#include "ObjectLoader.h"
#include "TiledSprite.h"
#include "TiledLevel.h"
#include "Player.h"
#include "TextPanel.h"
#include "Light.h"


using namespace std;
using namespace oxygine;


DECLARE_SMART(Level, spLevel);


class LevelInteractiveUnit : public InteractiveUnit
{
private:
    void free_text_panel(Event*);
    bool _is_text_panel_exist;

public:
    LevelInteractiveUnit() : _is_text_panel_exist(false), text("Забыли текст"){}
    LevelInteractiveUnit(const LevelInteractiveUnit& o):text(o.text){}
    virtual ~LevelInteractiveUnit(){}

    virtual void on_collideX(DynamicUnit*, ITiledLevel*, const uint) override;
    virtual void on_collideY(DynamicUnit*, ITiledLevel*, const uint) override;
    void kill_me(Event *);

    string text;
};


class StairsInteractiveUnit : public InteractiveUnit
{
public:
    StairsInteractiveUnit(){}
    StairsInteractiveUnit(const StairsInteractiveUnit&){}
    virtual ~StairsInteractiveUnit(){}

    virtual void on_collideY(DynamicUnit*, ITiledLevel*, const uint) override;
    virtual void on_collideX(DynamicUnit*, ITiledLevel*, const uint) override;
};


class LevelFinishUnit : public LevelInteractiveUnit
{
public:
    LevelFinishUnit(){}
    LevelFinishUnit(const LevelFinishUnit& o):LevelInteractiveUnit(o){}
    virtual ~LevelFinishUnit(){}

    virtual void on_collideX(DynamicUnit*, ITiledLevel*, const uint) override;
    virtual void on_collideY(DynamicUnit*, ITiledLevel*, const uint) override;
};


class Level : public ITiledLevel
{
private:
    spTiledSprite landscape;

    spPlayer player;

    vector<LevelInteractiveUnit> lius;
    LevelFinishUnit lfu;
    InteractiveUnit empty_iu;
    StairsInteractiveUnit stairs;

    spLightMaterial _light_material;

    void _load_terrain(const LAYERS&, Image&, const list<GameObject>&);

public:
    Level();
    Level(const Level& orig);
    virtual ~Level();

    void init() override;

    GameError load_stage(const string& fname);

    void doUpdate(const UpdateState& us) override;

    void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
    void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
};

#endif /* LEVEL_H */
