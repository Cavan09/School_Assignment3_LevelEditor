//
//  GroundTile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef TREE_TILE_H
#define TREE_TILE_H

#include "Tile.h"


class TreeTile : public Tile
{
public:
	TreeTile(const char* textureName = RES_TILE_TREE);
	virtual ~TreeTile();
  
    //Return the type of the tile
    const char* getType();
};

#endif
