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

    void set_light_pos(const float x, const float y);
    const Vector2 get_light_pos() const;

    void set_radius(const float radius);
    float get_radius() const;

    void set_intense(const float intense);
    float get_intense() const;

    void set_light_color(const Vector4&);
    const Vector4& get_light_color() const;

    void set_ambient_intense(const float ambient_intense);
    float get_ambient_intense() const;

};

#endif /* LIGHT_H */
