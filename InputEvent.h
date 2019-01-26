/* 
 * File:   InputEvent.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:41 AM
 */

#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <oxygine-framework.h>
#include "flags.h"
#include "base.h"


using namespace oxygine;


class InputEvent : public Base
{
public:
    InputEvent();
    InputEvent(const InputEvent& orig);
    virtual ~InputEvent();


    virtual void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) = 0;

    virtual void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) = 0;

};

#endif /* INPUTEVENT_H */
