/* 
 * File:   InputEvent.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:41 AM
 */
#include "InputEvent.h"


InputEvent::InputEvent()
{
#ifdef DBG
    logs::messageln("InputEvent:: ()");
#endif

    // Начнём слушать события
    core::getDispatcher()->addEventListener(core::EVENT_SYSTEM, CLOSURE(this, &InputEvent::_onSysEvent));
}

InputEvent::InputEvent(const InputEvent&)
{
#ifdef DBG
    logs::messageln("InputEvent:: Copy");
#endif
}

InputEvent::~InputEvent()
{
#ifdef DBG
    logs::messageln("InputEvent:: ~");
#endif
}


void InputEvent::_onSysEvent(Event* event)
{
    _onSDLEvent((SDL_Event*)event->userData);
}


void InputEvent::_onSDLEvent(SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
        {
            if(!_pressed_keys[event->key.keysym.scancode])
            {
                OnKeyDown(event->key, event->key.keysym.scancode);
                _pressed_keys[event->key.keysym.scancode] = true;
            }
        }
        break;
        case SDL_KEYUP:
        {
            if(_pressed_keys[event->key.keysym.scancode])
            {
                OnKeyUp(event->key, event->key.keysym.scancode);
                _pressed_keys[event->key.keysym.scancode] = false;
            }
        }
        break;
    }
}
