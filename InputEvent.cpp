/* 
 * File:   InputEvent.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:41 AM
 */
#include <algorithm>
#include <vector>
#include "InputEvent.h"


#ifdef DBG
#include <iostream>
#endif

using namespace std;


class InputEventContainer
{
private:
    InputEventContainer();
    InputEventContainer(const InputEventContainer&);
    virtual ~InputEventContainer();

    bool _pressed_keys[SDL_Scancode::SDL_NUM_SCANCODES];
    vector<InputEvent*> _obj_instances;

    //void _push_events(const SDL_Event* event);
    void push_key_up(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode);
    void push_key_down(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode);

public:
    void OnEvent(const SDL_Event* event);
    friend InputEvent;
};

InputEventContainer *gp_inp_event_cont = nullptr;

void _onEvent(Event* ev)
{
    SDL_Event *event = static_cast<SDL_Event*>(ev->userData);

    gp_inp_event_cont->OnEvent(event);
}


InputEventContainer::InputEventContainer()
{
    // Init system events
    ox::core::getDispatcher()->addEventListener(ox::core::EVENT_SYSTEM, _onEvent);

#ifdef DBG
    cout << "InputEventContainer::InputEventContainer" << endl;
#endif
}
InputEventContainer::InputEventContainer(const InputEventContainer&){}
InputEventContainer::~InputEventContainer(){}



void InputEventContainer::OnEvent(const SDL_Event* event)
{
    switch(event->type)
    {
        /*case SDL_ACTIVEEVENT: {
            switch(Event->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if ( Event->active.gain )    OnMouseFocus();
                    else                OnMouseBlur();

                    break;
                }
                case SDL_APPINPUTFOCUS: {
                    if ( Event->active.gain )    OnInputFocus();
                    else                OnInputBlur();

                    break;
                }
                case SDL_APPACTIVE:    {
                    if ( Event->active.gain )    OnRestore();
                    else                OnMinimize();

                    break;
                }
            }
            break;
        }*/

        case SDL_KEYDOWN:

            if(!_pressed_keys[event->key.keysym.scancode])
            {
                push_key_down(event->key, event->key.keysym.scancode);
                _pressed_keys[event->key.keysym.scancode] = true;
            }
            break;

        case SDL_KEYUP:

            if(_pressed_keys[event->key.keysym.scancode])
            {
                push_key_up(event->key, event->key.keysym.scancode);
                _pressed_keys[event->key.keysym.scancode] = false;
            }
            break;

        /*case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_JOYAXISMOTION: {
            OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
        }

        case SDL_JOYBALLMOTION: {
            OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
            break;
        }

        case SDL_JOYHATMOTION: {
            OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }

        case SDL_JOYBUTTONUP: {
            OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }

        case SDL_QUIT: {
            OnExit();
            break;
        }

        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }

        case SDL_VIDEORESIZE: {
            OnResize(Event->resize.w,Event->resize.h);
            break;
        }

        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }

        default: {
            OnUser(event);
            break;
        }*/
    }
}


void InputEventContainer::push_key_up(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    for(auto ev_obj : _obj_instances)
    {
        ev_obj->OnKeyUp(ev, key_scancode);
    }
}
void InputEventContainer::push_key_down(const SDL_KeyboardEvent& ev, const SDL_Scancode& key_scancode)
{
    for(auto ev_obj : _obj_instances)
    {
        ev_obj->OnKeyDown(ev, key_scancode);
    }
}









InputEvent::InputEvent()
{
#ifdef DBG
    cout << "InputEvent::InputEvent" << endl;
#endif

    static InputEventContainer inp_cont;
    gp_inp_event_cont = &inp_cont;

    inp_cont._obj_instances.push_back(this);

}

InputEvent::InputEvent(const InputEvent& orig)
{
#ifdef DBG
    cout << "InputEvent:: Copy" << endl;
#endif
}

InputEvent::~InputEvent()
{
#ifdef DBG
    cout << "InputEvent:: ~" << endl;
#endif

    // удалим себя из получателей событий
    auto &it = gp_inp_event_cont->_obj_instances;
    remove(it.begin(), it.end(), this);
}
