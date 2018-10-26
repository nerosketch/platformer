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
#include "GameStage.h"


using namespace std;
using namespace oxygine;


DECLARE_SMART(Level, spLevel);


class Level : public GameStage
{
private:
    INHERITED(GameStage);

    vector<Unit> units;
    spPlayer player;

public:
    Level();
    Level(const Level& orig);
    virtual ~Level();

    GameError load_stage(string fname);

    // карта для взаимодействий
    vector<vector<uint>> map_interaction;

    void doUpdate(const UpdateState& us) override;
};

#endif /* LEVEL_H */

