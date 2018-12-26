/* 
 * File:   Light.h
 * Author: ns
 *
 * Created on December 25, 2018, 1:22 AM
 */

#include <oxygine-framework.h>


using namespace oxygine;


#ifndef LIGHT_H
#define LIGHT_H


DECLARE_SMART(Light, spLight);


class Light :public Sprite
{
private:
    INHERITED(Sprite);
    UberShaderProgram* _shaderLight;

public:
    Light();
    Light(const Light& orig);
    virtual ~Light();
};

#endif /* LIGHT_H */
