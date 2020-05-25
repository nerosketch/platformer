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


using namespace oxygine;


class InputEvent
{
private:
    void _onSysEvent(Event* event);
    void _onSDLEvent(SDL_Event* event);
    bool _pressed_keys[SDL_Scancode::SDL_NUM_SCANCODES];

    void startListenEvents();
    void stopListenEvents();

public:
    InputEvent();
    InputEvent(const InputEvent&);
    virtual ~InputEvent();

    virtual void OnKeyDown(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) = 0;

    virtual void OnKeyUp(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode) = 0;

};

#endif /* INPUTEVENT_H */
