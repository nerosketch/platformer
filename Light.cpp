/* 
 * File:   Light.cpp
 * Author: ns
 * 
 * Created on December 25, 2018, 1:22 AM
 */

#include <string>
#include "Light.h"
#include "resources.h"


#define ADDR_BUF_LEN 32


DECLARE_SMART(CustomUniformMat, spCustomUniformMat);


class CustomUniformMat : public STDMaterial
{
private:
    char _addr_buf[ADDR_BUF_LEN];

public:
    MATX(CustomUniformMat);

    Light *p_light;

    static bool cmp(const CustomUniformMat& a, const CustomUniformMat& b)
    {
        if (!STDMaterial::cmp(a, b))
            return false;

        /*return a.light_pos_radius_intense == b.light_pos_radius_intense &&
                a.light_color == b.light_color &&
                a.ambient_intense == b.ambient_intense;*/
        return false;
    }

    void xapply() override
    {
        STDMaterial::xapply();

        IVideoDriver::instance->setUniformInt("lights_count", p_light->lights_count);
        IVideoDriver::instance->setUniform("ambient_intense", p_light->_ambient_intense);

        const Vector2& pos = p_light->getPosition();

        uint n = 0;
        for(const LightPoint& l : p_light->_lights)
        {
            if(n > 15)
                break;

            snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].light_pos", n);
            IVideoDriver::instance->setUniform(_addr_buf, l + pos);

            snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].light_color", n);
            IVideoDriver::instance->setUniform(_addr_buf, l._light_color);

            snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].radius", n);
            IVideoDriver::instance->setUniform(_addr_buf, l._radius);

            snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].intense", n);
            IVideoDriver::instance->setUniform(_addr_buf, l._intense);

            n++;
        }
    }
};


// #################### Light Start #####################


Light::Light() : _shaderLight(nullptr)
{
    applyShader(this);
}

Light::Light(const Light&)
{}

Light::~Light()
{
    delete _shaderLight;
}


void Light::applyShader(VStyleActor* p_actor)
{
    if(_shaderLight != nullptr)
    {
        delete _shaderLight;
        _shaderLight = nullptr;
    }

    ox::file::buffer data;
    ox::file::read("lighting.glsl", data);

    _shaderLight = new UberShaderProgram;
    _shaderLight->init(STDRenderer::uberShaderBody, data.getString().c_str());

    spCustomUniformMat mat(new CustomUniformMat);
    mat->p_light = this;
    p_actor->_mat->copyTo(*mat);

    mat->_uberShader = _shaderLight;

    _ambient_intense = 0.5f;
    lights_count = _lights.size();

    p_actor->_mat = mc().cache(*mat);
}


void Light::addLight(const LightPoint& p)
{
#ifdef DBG
    logs::messageln("Light::addLight %d", lights_count);
#endif

    _lights.push_back(p);
    lights_count = _lights.size();
}


void Light::removeLight(LightPoint& p)
{
    //CustomUniformMat *p_mat = static_cast<STDMaterial*>(_mat.get());
    //p_mat->_lights.push_back(p);
}


void Light::set_ambient_intense(const float ai)
{
    _ambient_intense = ai;
}


float Light::get_ambient_intense() const
{
    return _ambient_intense;
}


// #################### Light End #####################


// #################### LightPoint Start #####################


LightPoint::LightPoint() : _light_color(1.f, 1.f, 1.f, 1.f),
        _radius(200.f), _intense(1.f)
{}

LightPoint::LightPoint(const float x, const float y) : Vector2(x, y),
        _light_color(1.f, 1.f, 1.f, 1.f),
        _radius(200.f), _intense(1.f)
{
    set(x, y);
}


LightPoint::LightPoint(const Vector2& pos) : LightPoint(pos.x, pos.y)
{}


LightPoint::LightPoint(const LightPoint& o) :
        Vector2(o), _light_color(o._light_color),
        _radius(o._radius), _intense(o._intense)
{}


LightPoint::~LightPoint()
{}

// #################### LightPoint End #####################
