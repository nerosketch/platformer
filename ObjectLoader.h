/* 
 * File:   ObjectLoader.h
 * Author: ns
 *
 * Created on October 9, 2018, 6:44 PM
 */

#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <string>
#include <vector>
#include <sys/types.h>
#include <oxygine-framework.h>
#include <ox/json.hpp>
#include "flags.h"
#include "base.h"
#include "TiledSprite.h"

using namespace std;
using namespace oxygine;
using namespace Json;


typedef vector<LAYER> LAYERS;

class GameObject : public RectF
{
public:
    GameObject() : text("Забыли текст"){}
    GameObject(const Vector2& pos, const Vector2& size):
        RectF(pos, size){}
    GameObject(float x, float y, float w, float h):
        RectF(x, y, w, h){}
    GameObject(const GameObject& o):
        RectF(o.pos, o.size){text = o.text;}
    virtual ~GameObject(){}

    string text;
};


class ObjectLoader : public Base
{
private:
    void _load_objects(const Value&);

public:
    ObjectLoader();
    ObjectLoader(const ObjectLoader& orig);
    virtual ~ObjectLoader();

    LAYERS backgrounds;
    LAYERS terrains;
    LAYER landscape;
    vector<spTILESET> tilesets;
    list<GameObject> objects;
    Vector2 tile_size;

    spTILESET get_tileset_by_name(string name);
    spTILESET get_tileset_by_id(uint id);

    void open(const string fname);

};

#endif /* OBJECTLOADER_H */
