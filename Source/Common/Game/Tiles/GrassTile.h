
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef GRASS_TILE_H
#define GRASS_TILE_H

#include "Tile.h"


class GrassTile : public Tile
{
public:
	GrassTile(const char* textureName = RES_TILE_GRASS);
	virtual ~GrassTile();
  
    //Return the type of the tile
    const char* getType();
};

#endif