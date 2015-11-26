
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "PavedTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


PavedTile::PavedTile(const char* textureName) : Tile(TileTypePaved, textureName, true)
{

}

PavedTile::~PavedTile()
{

}

const char* PavedTile::getType()
{
    return TILE_PAVED_TYPE;
}