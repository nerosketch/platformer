/* 
 * File:   ITiledLevel.cpp
 * Author: bashmak
 * 
 * Created on 19 января 2019 г., 22:35
 */
#include "flags.h"
#include "TiledLevel.h"


ITiledLevel::ITiledLevel() : GameStage(), _map_size(0, 0),
_tile_size(TILE_WIDTH, TILE_HEIGHT),
gravity(0.0005f)
{}


ITiledLevel::ITiledLevel(const ITiledLevel& o) : _map_size(o._map_size),
_tile_size(o._tile_size),
gravity(o.gravity)
{}


ITiledLevel::~ITiledLevel()
{}
