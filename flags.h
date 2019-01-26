/* 
 * File:   flags.h
 * Author: ns
 *
 * Created on August 7, 2018, 10:28 PM
 */

#ifndef FLAGS_H
#define FLAGS_H


// Включаем звук
//#define SOUND_ENABLE

#ifdef _WIN32
#define uint unsigned int
#endif

#ifdef DBG
// Включаем debug отрисовку Box2D
//#define DEBUG_DRAW_ENABLE
#endif


#define TILE_WIDTH      16.f
#define TILE_HEIGHT     16.f


/*
 * core::init_desc `w` and `h`
 */
#define INITIAL_STAGE_WIDTH     960.f
#define INITIAL_STAGE_HEIGHT    540.f


#endif /* FLAGS_H */
