#include "resources.h"
#include "flags.h"

namespace res{
    Resources resources;
    void load(){
        resources.loadXML("res/res.xml");

#ifdef SOUND_ENABLE
        resources.loadXML("res/sounds.xml");
#endif

    }
    void free(){
        resources.free();
    }
}