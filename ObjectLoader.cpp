/* 
 * File:   ObjectLoader.cpp
 * Author: ns
 * 
 * Created on October 9, 2018, 6:44 PM
 */

#include "ox/json.hpp"
#include "ObjectLoader.h"


using namespace std;

ObjectLoader::ObjectLoader()
{
}

ObjectLoader::ObjectLoader(const ObjectLoader& orig)
{
}

ObjectLoader::~ObjectLoader()
{
}

void _load_tileset(struct TILESET *p_tileset, const string &fname)
{
    //load file to buffer
    ox::file::buffer bf;
    ox::file::read(fname, bf);

    //parse
    Json::Reader reader;
    Json::Value value;
    reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

    p_tileset->columns = value["columns"].asUInt();
    p_tileset->image = value["image"].asString();
    p_tileset->imageheight = value["imageheight"].asUInt();
    p_tileset->imagewidth = value["imagewidth"].asUInt();
    p_tileset->name = value["name"].asString();
    p_tileset->tilecount = value["tilecount"].asUInt();
    p_tileset->tileheight = value["tileheight"].asUInt();
    p_tileset->tilewidth = value["tilewidth"].asUInt();

}

void ObjectLoader::open(string fname)
{
    //load file to buffer
    ox::file::buffer bf;
    ox::file::read(fname, bf);

    //parse
    Json::Reader reader;
    Json::Value value;
    reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);


    uint tilesets_count = value["tilesets"].size();
    uint tilesets_counter = 0;
    tilesets.resize(tilesets_count);

    /*
     * Временный костыль. Все слои всегда указывают
     * на последний tileset. Потому что я не знаю как
     * в формате tiled связаны слой и tileset.
     */
    struct TILESET *p_last_tileset;

    for(const auto &v : value["tilesets"])
    {
        struct TILESET &tileset = tilesets[tilesets_counter++];

        string tileset_name = v["source"].asString();

        _load_tileset(&tileset, tileset_name);
        tileset.firstgid = v["firstgid"].asUInt();

        p_last_tileset = &tileset;
    }


    uint layers_count = value["layers"].size();
    uint layers_counter = 0;
    layers.resize(layers_count);

    for(const auto &v : value["layers"])
    {
        LAYER &lay = layers[layers_counter++];

        struct LAYER_OPTIONS &lay_opts = lay.options;

        lay.tileheight = v["tileheight"].asUInt();

        // Layer options
        lay_opts.height = v["height"].asUInt();
        lay_opts.width = v["width"].asUInt();
        lay_opts.opacity = v["opacity"].asFloat();
        lay_opts.visible = v["visible"].asBool();
        lay_opts.x = v["x"].asInt();
        lay_opts.y = v["y"].asInt();
        lay.p_tileset = p_last_tileset;
        //lay_opts.name = v["name"].asString();

        vector<int> &layer_data = lay.int_data;
        uint layer_data_size = v["data"].size();
        layer_data.resize(layer_data_size);

        uint n = 0;
        for(const auto &i : v["data"])
        {
            layer_data[n++] = i.asInt();
        }
    }

}

shared_ptr<Point> LAYER::get_coords(const uint block_index)
{
    shared_ptr<Point> p(new Point());

    const uint row_len = p_tileset->columns;

    // строка
    if(block_index == 0)
    {
        p->y = 0;
    }else
    {
        p->y = block_index / row_len;
        if(block_index % row_len == 0)
            p->y -= 1;
    }

    p->x = row_len - (((p->y+1) * row_len) - block_index) - 1;

    return p;
}


const struct TILESET *ObjectLoader::get_tileset_by_name(string name) const
{
    for(const auto &v : tilesets)
    {
        if(v.name == name)
        {
            return &v;
        }
    }
}
const struct TILESET *ObjectLoader::get_tileset_by_id(uint id) const
{
    for(const auto &v : tilesets)
    {
        if(v.firstgid == id)
        {
            return &v;
        }
    }
}

