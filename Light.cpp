/* 
 * File:   Light.cpp
 * Author: ns
 * 
 * Created on December 25, 2018, 1:22 AM
 */

#include "Light.h"
#include "resources.h"



class CustomUniformMat : public STDMaterial
{
public:
    MATX(CustomUniformMat);

    Vector4 light_pos_radius_intense = Vector4(455.f, 100.f, 200.f, 1.f);
    Vector4 light_color = Vector4(1.f, 1.f, 1.f, 1.f);
    float ambient_intense = 1.f;

    /*void rehash(size_t& hash) const override
    {
        logs::messageln("rehash");
        STDMaterial::rehash(hash);
        hash_combine(hash, light_pos.x, light_pos.y);
    }*/

    static bool cmp(const CustomUniformMat& a, const CustomUniformMat& b)
    {
        if (!STDMaterial::cmp(a, b))
            return false;

        return a.light_pos_radius_intense == b.light_pos_radius_intense &&
                a.light_color == b.light_color &&
                a.ambient_intense == b.ambient_intense;
    }

    void xapply() override
    {
        STDMaterial::xapply();
        IVideoDriver::instance->setUniform("light_pos_radius_intense", light_pos_radius_intense);
        IVideoDriver::instance->setUniform("light_color", light_color);
        IVideoDriver::instance->setUniform("ambient_intense", ambient_intense);
    }
};







Light::Light() : _shaderLight(0)
{
    _shaderLight = new UberShaderProgram;
    _shaderLight->init(STDRenderer::uberShaderBody, R"(
        #define MODIFY_BASE
        uniform lowp vec4 light_pos_radius_intense;
        uniform lowp vec4 light_color;
        uniform lowp float ambient_intense;
        lowp vec4 modify_base(lowp vec4 base)
        {
            base = base * light_color;
            float radius = light_pos_radius_intense.z;
            float dist = distance(light_pos_radius_intense.xy, gl_FragCoord.xy);
            if(dist < radius)
            {
                float k = 1.0 + ambient_intense - (dist / radius);
                return base * k * light_pos_radius_intense.a;
            }else
                return base * ambient_intense * light_pos_radius_intense.a;
        }
    )");

    CustomUniformMat mat;
    _mat->copyTo(mat);

    mat._uberShader = _shaderLight;
    _mat = mc().cache(mat);

    //setResAnim(res::resources.getResAnim("panel"));
}

Light::Light(const Light&)
{
}

Light::~Light()
{
    delete _shaderLight;
}


void Light::set_light_pos(const float x, const float y)
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    Vector4& lp = p_mat->light_pos_radius_intense;
    lp.x = x;
    lp.y = y;
}


const Vector2 Light::get_light_pos() const
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    const Vector4& lp = p_mat->light_pos_radius_intense;
    return Vector2(lp.x, lp.y);
}


void Light::set_radius(const float radius)
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    Vector4& lp = p_mat->light_pos_radius_intense;
    lp.z = radius;
}


float Light::get_radius() const
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    const Vector4& lp = p_mat->light_pos_radius_intense;
    return lp.z;
}


void Light::set_intense(const float intense)
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    Vector4& lp = p_mat->light_pos_radius_intense;
    lp.w = intense;
}


float Light::get_intense() const
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    const Vector4& lp = p_mat->light_pos_radius_intense;
    return lp.w;
}


void Light::set_light_color(const Vector4& c)
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    p_mat->light_color = c;
}


const Vector4& Light::get_light_color() const
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    return p_mat->light_color;
}


void Light::set_ambient_intense(const float ambient_intense)
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    p_mat->ambient_intense = ambient_intense;
}


float Light::get_ambient_intense() const
{
    CustomUniformMat *p_mat = static_cast<CustomUniformMat*>(_mat.get());
    return p_mat->ambient_intense;
}
