//Student: Cavan MacPhail
// Creation Date: Oct 30,2013
// Course Number: GAM1514
// Professor: Brad Flood
// Purpose: Game Logic



#include "Game.h"
#include "GameObject.h"
#include "Level.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Menus/LevelSlotMenu.h"


Game::Game() 

{
    //Create the level object
    //Reset everything
	m_Level = new Level();
	reset();
}

Game::~Game()
{
    //Delete the level object
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
}

void Game::update(double delta)
{
    if(m_Level != NULL)
    {
        m_Level->update(delta);
    }
}

void Game::paint()
{
    if(m_Level != NULL)
    {
        m_Level->paint();
    }
}

void Game::reset()
{
    if(m_Level != NULL)
    {
        m_Level->reset();
    }
}

const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}

Level* Game::getLevel()
{
    return m_Level;
}

void Game::mouseLeftClickUpEvent(float positionX, float positionY)
{
    if(m_Level != NULL)
    {
        m_Level->mouseLeftClickUpEvent(positionX, positionY);
    }
}

void Game::keyUpEvent(int keyCode)
{
    if(m_Level != NULL)
    {
        m_Level->keyUpEvent(keyCode);
    }  
}
void Game::setLevel(Level* level)
{
	m_Level = level;
}
