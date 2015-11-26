//Student: Cavan MacPhail
// Creation Date: Oct 30,2013
// Course Number: GAM1514
// Professor: Brad Flood
// Purpose: Player Logic

#include "Player.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>

Player::Player(Level* aLevel)
{
    //Initialize the current and destination tiles to NULL
    m_CurrentTile = NULL;
    m_DestinationTile = NULL;
    
    //Initialize the animation member variables
    m_CanAnimate = false;
    m_AbortAnimation = false;
    m_AnimationPathNodeIndex = -1;
    
    //Initialize the player's size
    setSize(PLAYER_SIZE, PLAYER_SIZE);
}

Player::~Player()
{
    //Set the current and desination tiles to NULL
	m_CurrentTile = NULL;
	m_DestinationTile = NULL;
}

void Player::update(double aDelta)
{
    if(m_DestinationTile != NULL)
    {
        setCurrentTile(m_DestinationTile);
    }
}

void Player::paint()
{
	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_INSIDE_COLOR);
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2);
	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_OUTLINE_COLOR);
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, false);
}

void Player::reset()
{
    m_DestinationTile = NULL;
}

const char* Player::getType()
{
    return PLAYER_TYPE;
}

void Player::setCurrentTile(Tile* tile)
{
	//Set the current tile pointer
	m_CurrentTile = tile;
    
	//Center the player's position on the tile
	setPosition(tile->getX() + ((tile->getWidth() - getWidth()) / 2), tile->getY() + ((tile->getHeight() - getHeight()) / 2));
}

void Player::setDestinationTile(Tile* tile)
{
	//Set the destination tile pointer
	m_DestinationTile = tile;
}

float Player::animate(float aCurrent, float aTarget, double aDelta)
{
    float increment = aDelta * PLAYER_SPEED * (aTarget < aCurrent ? -1 : 1);
    if(fabs(increment) > fabs(aTarget - aCurrent))
    {
        return aTarget;
    }
    else
    {
        aCurrent += increment;
    }
    return aCurrent;
}

void Player::startAnimating()
{
	m_CanAnimate = true;
	m_AnimationPathNodeIndex = 0;
}

void Player::stopAnimating()
{
	m_CanAnimate = false;
	m_AnimationPathNodeIndex = -1;
}

bool Player::isAnimating()
{
    return m_CanAnimate;
}
