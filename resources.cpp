#include "resources.h"
#include "flags.h"


namespace res{
    Resources resources;
    void load(const string& fname)
    {
#ifdef DBG
        logs::messageln("res::load %s", fname.c_str());
#endif
        resources.loadXML(fname);

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
