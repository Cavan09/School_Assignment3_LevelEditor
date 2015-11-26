
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef PAVED_TILE_H
#define PAVED_TILE_H

#include "Tile.h"


class PavedTile : public Tile
{
public:
	PavedTile(const char* textureName = RES_TILE_PAVED);
	virtual ~PavedTile();
  
    //Return the type of the tile
    const char* getType();
};

#endif