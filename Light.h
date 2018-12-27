/* 
 * File:   Light.h
 * Author: ns
 *
 * Created on December 25, 2018, 1:22 AM
 */

#include "flags.h"
#include <oxygine-framework.h>


using namespace oxygine;


#ifndef LIGHT_H
#define LIGHT_H


DECLARE_SMART(Light, spLight);


class LightPoint : public Vector2
{
private:
    friend class CustomUniformMat;
    Vector4 _light_color;
    //Vector2 _light_pos;
    float _radius;
    float _intense;

public:
    LightPoint();
    LightPoint(float x, float y);
    LightPoint(const LightPoint&);
    virtual ~LightPoint();

    inline void set_radius(const float radius)
    {
        _radius = radius;
    }
    inline float get_radius() const
    {
        return _radius;
    }

    inline void set_intense(const float intense)
    {
        _intense = intense;
    }
    inline float get_intense() const
    {
        return _intense;
    }

    inline void set_light_color(const Vector4& c)
    {
        _light_color = c;
    }
    inline const Vector4& get_light_color() const
    {
        return _light_color;
    }

};


class Light :public Sprite
{
private:
    INHERITED(Sprite);
    UberShaderProgram* _shaderLight;

public:
    Light();
    Light(const Light& orig);
    virtual ~Light();

    void add_light(const LightPoint&);
    void remove_light(LightPoint&);

    void set_ambient_intense(const float);
    float get_ambient_intense() const;

};

#endif /* LIGHT_H */
