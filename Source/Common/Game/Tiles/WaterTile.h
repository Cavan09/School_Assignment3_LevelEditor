
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef WATER_TILE_H
#define WATER_TILE_H

#include "Tile.h"


class WaterTile : public Tile
{
public:
	WaterTile(const char* textureName = RES_TILE_WATER);
	virtual ~WaterTile();
  
    //Return the type of the tile
    const char* getType();
};

#endif