#include "resources.h"
#include "flags.h"

#ifdef DBG
#include <iostream>
#endif


namespace res{
    Resources resources;
    void load(const string &res_name)
    {
#ifdef DBG
        cout << "res::load " << res_name << endl;
#endif
        resources.loadXML(res_name);

#ifdef SOUND_ENABLE
        resources.loadXML("res/sounds.xml");
#endif

    }
    void free()
    {
#ifdef DBG
        cout << "res::free" << endl;
#endif
        resources.free();
    }
}
