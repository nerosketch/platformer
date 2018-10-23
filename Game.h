/* 
 * File:   Game.h
 * Author: ns
 *
 * Created on October 21, 2018, 10:53 AM
 */

#ifndef GAME_H
#define GAME_H

#include "base.h"

class Game : public Base
{
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();

    void preinit();
    GameError init();
    void destroy();
    void update();
    void flush();

private:

};

#endif /* GAME_H */

