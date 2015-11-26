//
//  GroundTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "TreeTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


TreeTile::TreeTile(const char* textureName) : Tile(TileTypeTree, textureName, false)
{

}

TreeTile::~TreeTile()
{

}

const char* TreeTile::getType()
{
    return TILE_TREE_TYPE;
}