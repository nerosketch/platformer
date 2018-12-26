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

    Vector3 light_pos_intensity = Vector3(455.f, 100.f, 200.f);

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

        return a.light_pos_intensity == b.light_pos_intensity;
    }

    void xapply() override
    {
        STDMaterial::xapply();
        static float intens=1.f;
        static float incr = 1.f;
        if(intens >= 500.f || intens <= 0.f)
            incr = -incr;
        intens += incr;
        light_pos_intensity.z = intens;
        IVideoDriver::instance->setUniform("light_pos_intensity", light_pos_intensity);
    }
};







Light::Light() : _shaderLight(0)
{
    _shaderLight = new UberShaderProgram;
    _shaderLight->init(STDRenderer::uberShaderBody, R"(
        #define MODIFY_BASE
        uniform lowp vec3 light_pos_intensity;
        lowp vec4 modify_base(lowp vec4 base)
        {
            float dist = distance(light_pos_intensity.xy, gl_FragCoord.xy);
            return base * (light_pos_intensity.z/dist);
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
