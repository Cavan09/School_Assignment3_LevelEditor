//
//  GroundTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "RockTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


RockTile::RockTile(const char* textureName) : Tile(TileTypeRock, textureName, false)
{

}

RockTile::~RockTile()
{

}

const char* RockTile::getType()
{
    return TILE_ROCK_TYPE;
}