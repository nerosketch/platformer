/* 
 * File:   Player.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:48 AM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <oxygine-framework.h>
#include "DynamicUnit.h"


using namespace oxygine;

DECLARE_SMART(Player, spPlayer);


class Player : public DynamicUnit
{
private:
    uint level;
public:
    Player(const Vector2 &pos);
    Player(const Player& orig);
    virtual ~Player();

    GameError init() override;

    void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;

    void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) override;
};

#endif /* PLAYER_H */

