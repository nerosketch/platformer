/* 
 * File:   Level.h
 * Author: ns
 *
 * Created on October 21, 2018, 9:43 AM
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <oxygine-framework.h>
#include "ObjectLoader.h"
#include "InputEvent.h"
#include "TiledSprite.h"
#include "GameStage.h"
#include "Unit.h"
#include "TextPanel.h"


using namespace std;
using namespace oxygine;


DECLARE_SMART(Level, spLevel);


class LevelInteractiveUnit : public InteractiveUnit
{
public:
    LevelInteractiveUnit();
    LevelInteractiveUnit(const LevelInteractiveUnit&);
    virtual ~LevelInteractiveUnit();

    TextPanel *p_text_panel;

    virtual void on_collide(DynamicUnit*) override;
    void kill_me(Event *);
};


class Level : public GameStage, public InputEvent
{
private:
    INHERITED(GameStage);

    spTiledSprite landscape;

    spPlayer player;

    LevelInteractiveUnit liu;
    InteractiveUnit empty_iu;

    void _load_terrain(const vector<LAYER>&, Image&, const list<RectF>&);

public:
    Level();
    Level(const Level& orig);
    virtual ~Level();

    GameError load_stage(const string fname);

    // карта для взаимодействий
    vector<vector<InteractiveUnit*>> map_interaction;

    void doUpdate(const UpdateState& us) override;

    void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
    void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
};

#endif /* LEVEL_H */
