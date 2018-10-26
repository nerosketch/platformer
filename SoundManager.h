/* 
 * File:   SoundManager.h
 * Author: ns
 *
 * Created on August 2, 2018, 12:48 AM
 */
#include "flags.h"
#ifdef SOUND_ENABLE

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>

#include <oxygine-sound.h>
#include "resources.h"

using namespace oxygine;
using namespace std;

class SoundManager: public SoundPlayer
{
public:
    SoundManager();
    SoundManager(const SoundManager& orig);
    virtual ~SoundManager();
    
    void doUpdate();
    
    void startBackground()
    {
        play_from_name("8bit_universe");
    }
    
    void play_from_name(const string);
private:

};

#endif
#endif /* SOUNDMANAGER_H */

