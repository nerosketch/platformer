/* 
 * File:   Light.cpp
 * Author: ns
 * 
 * Created on December 25, 2018, 1:22 AM
 */

#include <vector>
#include <string>
#include "Light.h"
#include "resources.h"


using namespace std;

#define ADDR_BUF_LEN 32

class CustomUniformMat : public STDMaterial
{
private:
    char _addr_buf[ADDR_BUF_LEN];
public:
    MATX(CustomUniformMat);

    vector<LightPoint> _lights;
    uint lights_count = 0;
    float _ambient_intense=1.f;

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

        IVideoDriver::instance->setUniformInt("lights_count", lights_count);
        IVideoDriver::instance->setUniform("ambient_intense", _ambient_intense);
        uint n = 0;
        for(const LightPoint& l : _lights)
        {
            if(n > 15)
                break;

            snprintf(_addr_buf, ADDR_BUF_LEN, "lights[%d].light_pos", n);
            IVideoDriver::instance->setUniform(_addr_buf, l);

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


Light::Light() : _shaderLight(0)
{
    _shaderLight = new UberShaderProgram;
    _shaderLight->init(STDRenderer::uberShaderBody, R"(
        #define MODIFY_BASE
        struct LIGHT_INFO{
            vec4 light_color;
            vec2 light_pos;
            float radius;
            float intense;
        };
        uniform lowp int lights_count;
        uniform lowp float ambient_intense;
        uniform lowp LIGHT_INFO lights[16];

        lowp vec4 modify_base(lowp vec4 base)
        {

            for(int i = 0; i < lights_count; ++i)
            {
                base *= lights[i].light_color;
                float dist = distance(lights[i].light_pos, gl_FragCoord.xy);
                if(dist < lights[i].radius)
                {
                    float k = 1.0 - (dist / lights[i].radius);
                    base *= lights[i].intense * k;
                }else
                {
                    base *= lights[i].intense;
                }
            }
            return base * ambient_intense;
        }
    )");

    /*
     * Часть успешного шейдера
    base = base * light2.light_color;
    dist = distance(lights[n].light_pos, gl_FragCoord.xy);
    if(dist < lights[n].radius)
    {
        k += 1.0 + lights[n].ambient_intense - (dist / lights[n].radius);
        base = base * k * light2.intense;
    }else
        base = base * light2.ambient_intense * light2.intense;
    */

    CustomUniformMat mat;
    _mat->copyTo(mat);

    mat._uberShader = _shaderLight;
    mat._lights.resize(2);
    mat._lights[0] = LightPoint(555.f, 100.f);
    
    Vector4 light_color(0.5f, 0.5f, 0.9f, 0.0f);
    mat._lights[0].set_light_color(light_color);
    mat._lights[0].set_intense(3.8f);
    mat._lights[0].set_radius(40.f);

    mat._lights[1] = LightPoint(255.f, 100.f);
    light_color = Vector4(0.9f, 0.5f, 0.5f, 0.0f);
    mat._lights[1].set_light_color(light_color);
    mat._lights[1].set_intense(1.8f);

    set_ambient_intense(0.4f);

    mat.lights_count = mat._lights.size();

    _mat = mc().cache(mat);

}

Light::Light(const Light&)
{
}

Light::~Light()
{
    delete _shaderLight;
}


void Light::add_light(const LightPoint& p)
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    p_mat->_lights.push_back(p);
    p_mat->lights_count = p_mat->_lights.size();
}

void Light::remove_light(LightPoint& p)
{
    //CustomUniformMat *p_mat = static_cast<STDMaterial*>(_mat.get());
    //p_mat->_lights.push_back(p);
}

void Light::set_ambient_intense(const float ai)
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    p_mat->_ambient_intense = ai;
}

float Light::get_ambient_intense() const
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    return p_mat->_ambient_intense;
}


// #################### Light End #####################


// #################### LightPoint Start #####################


LightPoint::LightPoint() : _light_color(1.f, 1.f, 1.f, 1.f),
        _radius(200.f), _intense(1.f)
{}

LightPoint::LightPoint(float x, float y) : Vector2(x, y),
        _light_color(1.f, 1.f, 1.f, 1.f),
        _radius(200.f), _intense(1.f)
{
    set(x, y);
}

LightPoint::LightPoint(const LightPoint& o) :
        Vector2(o), _light_color(o._light_color),
        _radius(o._radius), _intense(o._intense)
{}

LightPoint::~LightPoint()
{}

// #################### LightPoint End #####################
