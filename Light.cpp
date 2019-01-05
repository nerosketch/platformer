/* 
 * File:   Light.cpp
 * Author: ns
 * 
 * Created on January 5, 2019, 6:17 PM
 */

#include "flags.h"
#include "Light.h"


class InitInConstructorUberShaderProgram : public UberShaderProgram
{
public:
    InitInConstructorUberShaderProgram() : UberShaderProgram()
    {
#ifdef DBG
        logs::messageln("InitInConstructorUberShaderProgram()");
#endif

        ox::file::buffer data;
        ox::file::read("lighting.glsl", data);

        init(STDRenderer::uberShaderBody, data.getString().c_str());
        
    }
    //InitInConstructorUberShaderProgram(const InitInConstructorUberShaderProgram&);
    virtual ~InitInConstructorUberShaderProgram()
    {
#ifdef DBG
        logs::messageln("InitInConstructorUberShaderProgram ~");
#endif
    }
};



// #################### LightMaterial Start #####################

uint LightMaterial::_lights_count = 0;
std::list<LightPoint*> LightMaterial::_light_points;


void LightMaterial::init()
{
#ifdef DBG
    logs::messageln("LightMaterial::init()");
#endif

    _ambient_intense = 0.5f;

    static InitInConstructorUberShaderProgram _shader;
    _uberShader = &_shader;
}

LightMaterial::LightMaterial(VStyleActor* p_actor)
{
    init();
    applyMateralTo(p_actor);
}


void LightMaterial::applyMateralTo(VStyleActor* p_actor)
{
    UberShaderProgram *p_sh = _uberShader;
    p_actor->_mat->copyTo(*this);
    _uberShader = p_sh;
    p_actor->_mat = mc().cache(*this);
}


LightMaterial::~LightMaterial()
{
#ifdef DBG
    logs::messageln("LightMaterial:: ~");
#endif
}


bool LightMaterial::cmp(const LightMaterial& a, const LightMaterial& b)
{
    if (!STDMaterial::cmp(a, b))
        return false;

    /*return a.light_pos_radius_intense == b.light_pos_radius_intense &&
            a.light_color == b.light_color &&
            a.ambient_intense == b.ambient_intense;*/
    return false;
}

void LightMaterial::xapply()
{
    STDMaterial::xapply();

    IVideoDriver::instance->setUniformInt("lights_count", _lights_count);
    IVideoDriver::instance->setUniform("ambient_intense", _ambient_intense);

    uint n = 0;
    for(const LightPoint *l : LightMaterial::_light_points)
    {
        if(n > 15)
            break;

//#ifdef DBG
//        const Vector2& p = l->getPosition();
//        logs::messageln("TmpPos x=%f, y=%f", p.x, p.y);
//#endif
        
        snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].light_pos", n);
        IVideoDriver::instance->setUniform(_addr_buf, l->getPosition());

        snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].light_color", n);
        IVideoDriver::instance->setUniform(_addr_buf, l->getLightColor());

        snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].radius", n);
        IVideoDriver::instance->setUniform(_addr_buf, l->getRadius());

        snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].intense", n);
        IVideoDriver::instance->setUniform(_addr_buf, l->getIntense());

        n++;
    }
}


void LightMaterial::_addLightPoint(LightPoint *p_light_point)
{
    _light_points.push_back(p_light_point);
    _lights_count = _light_points.size();
}


void LightMaterial::_delLightPoint(LightPoint *p_light_point)
{
    _light_points.remove(p_light_point);
    _lights_count = _light_points.size();
}


// #################### LightMaterial End #####################




// #################### LightPoint Start #####################


LightPoint::LightPoint() : LightPoint(0.f, 0.f)
{
#ifdef DBG
    logs::messageln("LightPoint::LightPoint()");
#endif
}


LightPoint::LightPoint(const float x, const float y) :
        _light_color(1.f, 1.f, 1.f, 1.f),
        _radius(200.f), _intense(1.f)
{
#ifdef DBG
    logs::messageln("LightPoint::LightPoint(const float x, const float y)");
#endif

    setPosition(x, y);

    LightMaterial::_addLightPoint(this);
}


LightPoint::LightPoint(const Vector2& pos) : LightPoint(pos.x, pos.y)
{
#ifdef DBG
    logs::messageln("LightPoint::LightPoint(const Vector2)");
#endif
}


LightPoint::LightPoint(const LightPoint& o) :
        Actor(o), _light_color(o._light_color),
        _radius(o._radius), _intense(o._intense)
{
#ifdef DBG
    logs::messageln("LightPoint:: copy");
#endif

    LightMaterial::_addLightPoint(this);
}


LightPoint::~LightPoint()
{
#ifdef DBG
    logs::messageln("LightPoint:: ~");
#endif

    LightMaterial::_delLightPoint(this);
}

// #################### LightPoint End #####################
