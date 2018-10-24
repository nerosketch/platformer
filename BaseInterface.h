/* 
 * File:   BaseInterface.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:44 AM
 */

#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

#include <oxygine-framework.h>
#include "base.h"


using namespace oxygine;


class BaseInterface : public Base, public Sprite
{
public:
    BaseInterface();
    BaseInterface(const BaseInterface& orig);
    virtual ~BaseInterface();
private:

};

#endif /* BASEINTERFACE_H */

