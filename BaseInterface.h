/* 
 * File:   BaseInterface.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:44 AM
 */

#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

#include "BaseSprite.h"


class BaseInterface : public BaseSprite
{
public:
    BaseInterface();
    BaseInterface(const BaseInterface& orig);
    virtual ~BaseInterface();
private:

};

#endif /* BASEINTERFACE_H */

