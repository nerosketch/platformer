#include "resources.h"
#include "flags.h"


namespace res{
    Resources resources;
    void load()
    {
#ifdef DBG
        logs::messageln("res::load res/res.xml");
#endif
        resources.loadXML("res/res.xml");

#ifdef SOUND_ENABLE
        resources.loadXML("res/sounds.xml");
#endif

    }
    void free()
    {
#ifdef DBG
        logs::messageln("res::free");
#endif
        resources.free();
    }
}
