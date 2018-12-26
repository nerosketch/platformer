#include "resources.h"
#include "flags.h"


namespace res{
    Resources resources;
    void load(const string &res_name)
    {
#ifdef DBG
        logs::messageln("res::load %s", res_name.c_str());
#endif
        resources.loadXML(res_name);

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
