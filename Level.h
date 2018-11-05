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
#include "GameStage.h"


using namespace std;
using namespace oxygine;


DECLARE_SMART(Level, spLevel);


class Level : public GameStage, public InputEvent
{
private:
    INHERITED(GameStage);
    
    spSprite background_image;

    vector<Unit> units;
    spPlayer player;

    void _load_terrain(LAYER&, const ResAnim*);
    void _load_background(LAYER&, const ResAnim*);

public:
    Level();
    Level(const Level& orig);
    virtual ~Level();

    GameError load_stage(const string fname);

    // карта для взаимодействий
    vector<vector<uint>> map_interaction;

    void doUpdate(const UpdateState& us) override;

    void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
    void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
};

#endif /* LEVEL_H */

