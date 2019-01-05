/* 
 * File:   Light.h
 * Author: ns
 *
 * Created on January 5, 2019, 6:17 PM
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <list>
#include <oxygine-framework.h>


using namespace oxygine;


DECLARE_SMART(LightMaterial, spLightMaterial);
DECLARE_SMART(LightPoint, spLightPoint);


#define ADDR_BUF_LEN 32


class LightPoint : public Actor
{
private:
    INHERITED(Actor);

    Vector4 _light_color;
    float _radius;
    float _intense;

public:
    LightPoint();
    LightPoint(const float x, const float y);
    LightPoint(const Vector2& pos);
    LightPoint(const LightPoint&);
    virtual ~LightPoint();

    inline void setRadius(const float radius)
    {
        _radius = radius;
    }
    inline float getRadius() const
    {
        return _radius;
    }
    inline void setIntense(const float intense)
    {
        _intense = intense;
    }
    inline float getIntense() const
    {
        return _intense;
    }
    inline void setLightColor(const Vector4& c)
    {
        _light_color = c;
    }
    inline void setLightColor(const Color& c)
    {
        _light_color = c.toVector();
    }
    inline void setLightColor(const uint c)
    {
        _light_color = Color::fromRGBA(c).toVector();
    }
    inline const Vector4& getLightColor() const
    {
        return _light_color;
    }
};



class LightMaterial : public STDMaterial
{
private:
    friend class LightPoint;

    char _addr_buf[ADDR_BUF_LEN];
    static std::list<LightPoint*> _light_points;
    static uint _lights_count;
    float _ambient_intense;

    static void _addLightPoint(LightPoint*);
    static void _delLightPoint(LightPoint*);

public:
    MATX(LightMaterial);
    LightMaterial(VStyleActor*);
    virtual ~LightMaterial();

    void init() override;

    void applyMateralTo(VStyleActor*);

    static bool cmp(const LightMaterial& a, const LightMaterial& b);

    void xapply() override;

    inline void setAmbientIntense(const float ai)
    {
        _ambient_intense = ai;
    }

    inline float getAmbientIntense() const
    {
        return _ambient_intense;
    }
};


#endif /* LIGHT_H */
