/* 
 * File:   InputEvent.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:41 AM
 */

#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <vector>
#include <oxygine-framework.h>
#include "base.h"


using namespace oxygine;
using namespace std;


class InputEvent : public Base
{
public:
    InputEvent();
    InputEvent(const InputEvent& orig);
    virtual ~InputEvent();


    virtual void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode){};

    virtual void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode){};

};

#endif /* INPUTEVENT_H */
