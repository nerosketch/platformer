/* 
 * File:   Landscape.h
 * Author: ns
 *
 * Created on November 8, 2018, 9:38 PM
 */

#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <oxygine-framework.h>
#include "flags.h"
#include "ObjectLoader.h"

using namespace oxygine;


DECLARE_SMART(Landscape, spLandscape);


class Landscape : public Sprite
{
    INHERITED(Sprite);
public:
    Landscape(const LAYER&, const ResAnim*);
    Landscape(const Landscape& orig);
    virtual ~Landscape();
};

#endif /* LANDSCAPE_H */
