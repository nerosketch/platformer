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
#include "oxygine-framework.h" 
#include "base.h"

using namespace std;
using namespace oxygine;



struct LAYER_OPTIONS
{
    uint width;
    uint height;
    float opacity;
    bool visible;
    float x;
    float y;
    short z_order;
    //string name;
};


struct TILESET
{
    uint firstgid;
    uint columns;
    string image;
    string name;
    uint imageheight;
    uint imagewidth;
    uint tilecount;
    uint tileheight;
    uint tilewidth;
};


class LAYER
{
public:
    struct LAYER_OPTIONS options;
    vector<uint> int_data;
    uint tileheight;

    Point get_coords(const uint block_index) const;

    struct TILESET *p_tileset;

};


class ObjectLoader : public Base {
public:
    ObjectLoader();
    ObjectLoader(const ObjectLoader& orig);
    virtual ~ObjectLoader();

    vector<LAYER> backgrounds;
    vector<LAYER> terrains;
    LAYER landscape;
    vector<struct TILESET> tilesets;

    const struct TILESET *get_tileset_by_name(string name) const;
    const struct TILESET *get_tileset_by_id(uint id) const;

    void open(const string fname);

};

#endif /* OBJECTLOADER_H */
