#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../../OpenGL/OpenGLColor.h"

//Game Constants
extern const char* GAME_SCREEN_NAME;

//Tile Constants
extern const char* TILE_GROUND_TYPE;
extern const char* TILE_TREE_TYPE;
extern const char* TILE_ROCK_TYPE;
extern const char* TILE_WATER_TYPE; 
extern const char* TILE_GRASS_TYPE;
extern const char* TILE_PAVED_TYPE;
extern const int TILE_PADDING;

//Player Constants
extern const char* PLAYER_TYPE;
extern const int PLAYER_SIZE;
extern const float PLAYER_SPEED;
extern const OpenGLColor PLAYER_INSIDE_COLOR;
extern const OpenGLColor PLAYER_OUTLINE_COLOR;

#endif 