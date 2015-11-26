//
//  Player.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <vector>

class Level;
class Tile;

class Player : public GameObject
{
public:
	Player(Level* level);
	virtual ~Player();

  //Update, paint and reset methods
	void update(double delta);
	void paint();
  void reset();
  
  //Implementing GameObject's pure virtual method
  const char* getType();
  
  //Setter methods for the current and destination tiles
	void setCurrentTile(Tile* tile);
	void setDestinationTile(Tile* tile);

protected:
  //Animation methods
  float animate(float current, float target, double delta);
	void startAnimating();
	void stopAnimating();
  bool isAnimating();

private:
	Tile* m_CurrentTile;
	Tile* m_DestinationTile;
	bool m_CanAnimate;
  bool m_AbortAnimation;
	int m_AnimationPathNodeIndex;
};

#endif