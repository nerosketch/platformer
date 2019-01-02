/* 
 * File:   Game.h
 * Author: ns
 *
 * Created on October 21, 2018, 10:53 AM
 */

#ifndef GAME_H
#define GAME_H

#include "StageManager.h"
#include "base.h"

class Game : public Base
{
private:
    spStageManager stage_manager;
    Rect _viewport;
    Color _clearColor;

public:
    Game();
    Game(const Game&);
    virtual ~Game();

    void preinit();
    GameError init();
    void destroy();
    bool update();
    void flush();

    inline const Rect& getViewport() const
    {
        return _viewport;
    }

    inline void setViewport(const Rect& r)
    {
        _viewport = r;
    }

    inline const Color& getClearColor() const
    {
        return _clearColor;
    }

    inline void setClearColor(const Color& c)
    {
        _clearColor = c;
    }
};

#endif /* GAME_H */

