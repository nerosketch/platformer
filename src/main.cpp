#include <ox/oxygine.hpp>
#include <ox/Stage.hpp>
#include <ox/DebugActor.hpp>

#include "Game.h"


using namespace std;
using namespace oxygine;


// This function is called each frame
bool mainloop(Game& gstage)
{
    // Update engine-internal components
    // If input events are available, they are passed to Stage::instance.handleEvent
    // If the function returns true, it means that the user requested the application to terminate
    bool done = core::update();

    if(gstage.update())
    {
        return true;
    }

    const spStage& p_stage = getStage();

    // Update our stage
    // Update all actors. Actor::update will also be called for all its children
    p_stage->update();

    if (core::beginRendering())
    {
        // Render all actors inside the stage. Actor::render will also be called for all its children
        //p_stage->render(clearColor, viewport);
        p_stage->render(gstage.getClearColor(), gstage.getViewport());

        core::swapDisplayBuffers();
    }

    return done;
}

// Application entry point
void run()
{
#ifdef DBG
    ObjectBase::__startTracingLeaks();
#endif

    // Initialize Oxygine's internal stuff
    core::init_desc desc;
    desc.title = "Yumi gift";

    // The initial window size can be set up here on SDL builds, ignored on Mobile devices
    //desc.w = 960;
    //desc.h = 540;
    desc.w = 1440;
    desc.h = 810;

    Game stage;


    stage.preinit();
    core::init(&desc);


    // Create the stage. Stage is a root node for all updateable and drawable objects
    Stage::instance = new Stage();
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

#ifdef DBG
    // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff
    DebugActor::show();
#endif

    GameError err = stage.init();
    if(err != 0)
    {
        ObjectBase::dumpCreatedObjects();
        ObjectBase::__stopTracingLeaks();
        stage.destroy();
        core::release();
        logs::error("ERROR: %s", err);
        return;
    }

#ifdef EMSCRIPTEN
    /*
    If you build for Emscripten, mainloop is called automatically and shouldn't be called here.
    See emscripten_set_main_loop in the EMSCRIPTEN section below
    */
    return;
#endif



#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
    // On iPhone mainloop is called automatically by CADisplayLink, see int main() below
    //return;
#endif

    Rect viewport(Point(0, 0), core::getDisplaySize());
    stage.setViewport(viewport);

    // This is the main game loop.
    while (1)
    {
        bool done = mainloop(stage);
        if (done)
            break;
    }

#ifdef DBG
    /*
     If we get here, the user has requested the Application to terminate.
     We dump and log all our created objects that have not been freed yet
    */
    ObjectBase::dumpCreatedObjects();
#endif

    /*
    Let's clean up everything right now and call ObjectBase::dumpObjects() again.
    We need to free all allocated resources and delete all created actors.
    All actors/sprites are smart-pointer objects and don't need to be removed by hand.
    But now we want to delete it by hand.
    */

    stage.destroy();


    //renderer.cleanup();

    // Releases all internal components and the stage
    core::release();

#ifdef DBG
    // The dump list should be empty by now,
    // we want to make sure that there aren't any memory leaks, so we call it again.
    ObjectBase::dumpCreatedObjects();

    ObjectBase::__stopTracingLeaks();
    //end
#endif
}

#ifdef OXYGINE_SDL

#include "SDL_main.h"
#include "SDL.h"

extern "C"
{
    /*void one(void* param) { mainloop(); }
    void oneEmsc() { mainloop(); }*/

    int main(int argc, char* argv[])
    {

        run();

/*#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
        // If parameter 2 is set to 1, refresh rate will be 60 fps, 2 - 30 fps, 3 - 15 fps.
        //SDL_iPhoneSetAnimationCallback(core::getWindow(), 1, one, nullptr);
#endif

#if EMSCRIPTEN
        emscripten_set_main_loop(oneEmsc, 0, 0);
#endif
*/
        return 0;
    }
};
#endif
