#ifdef PS


#define MODIFY_BASE

struct LIGHT_INFO{
    vec4 light_color;
    vec2 light_pos;
    float radius;
    float intense;
};

uniform lowp int lights_count;
uniform lowp float ambient_intense;
uniform lowp LIGHT_INFO lights[8];


lowp vec4 modify_base(lowp vec4 base)
{
    for(int i = 0; i < lights_count; ++i)
    {
        float dist = distance(lights[i].light_pos, gl_FragCoord.xy);
        if(dist < lights[i].radius)
        {
            float k = 1.0 - (dist / lights[i].radius) + ambient_intense * 2.0;
            base.rgb *= lights[i].light_color.rgb * lights[i].intense * k;
        }
    }
    base.rgb *= ambient_intense;
    return base;
}


#endif
