//Student: Cavan MacPhail
// Creation Date: Oct 30,2013
// Course Number: GAM1514
// Professor: Brad Flood
// Purpose: Level Creation

#include "Level.h"
#include "Player.h"
#include "Tiles/Tile.h"
#include "Tiles/GroundTile.h"
#include "Tiles/RockTile.h"
#include "Tiles/TreeTile.h"
#include "Tiles/WaterTile.h"
#include "Tiles/GrassTile.h"
#include "Tiles/PavedTile.h"
#include "../Math/GDRandom.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include <stdlib.h>
#include <fstream>
#include "../Constants/Game/GameConstants.h"
#include "../Utils/Logger/Logger.h"


Level::Level(bool isEditingLevel) :
    m_HorizontalTiles(0),
    m_VerticalTiles(0),
    m_TileSize(EMPTY_LEVEL_TILE_SIZE),
    m_PlayerStartingTileIndex(EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX),
    m_Player(NULL),
    m_Tiles(NULL),
    m_SelectedTileIndex(-1),
    m_PaintTileScoring(false),
    m_PaintTileIndexes(false)
{
    //Create the player object
    if(isEditingLevel == false)
    {
        m_Player = new Player(this);
    }
    
    //Calculate the number of horizontal and vertical tiles
    m_HorizontalTiles = ScreenManager::getInstance()->getScreenWidth() / m_TileSize;
    m_VerticalTiles = ScreenManager::getInstance()->getScreenHeight() / m_TileSize;
    
    //Allocate the tiles array, the inheriting class will populate this array with Tile objects
	m_Tiles = new Tile*[m_HorizontalTiles * m_VerticalTiles];
    
    //Initialize all the tiles to NULL
    for(int i = 0; i < m_HorizontalTiles * m_VerticalTiles; i++)
    {
        m_Tiles[i] = NULL;
    }
    
    //Load an empty level
    load(NULL);
}

Level::~Level()
{
    //Delete the player object
	if(m_Player != NULL)
	{
		delete m_Player;
		m_Player = NULL;		
	}
    
    //Delete the tiles array, the inheriting class
    //must delete the object in this array itself
	if(m_Tiles != NULL)
	{
        //Cycle through and delete all the tile objects in the array
        for(int i = 0; i < getNumberOfTiles(); i++)
        {
            if(m_Tiles[i] != NULL)
            {
                delete m_Tiles[i];
                m_Tiles[i] = NULL;
            }
        }
        
		delete[] m_Tiles;
		m_Tiles = NULL;
	}
}

void Level::update(double aDelta)
{
	//Update all the game tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->update(aDelta);
		}
	}
    
	//Update the Player
	if(m_Player != NULL)
	{
		m_Player->update(aDelta);
	}
}

void Level::paint()
{
	//Cycle through and paint all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
        //Safety check the tile
		if(m_Tiles[i] != NULL)
		{
            //Paint the tile
            m_Tiles[i]->paint();
            
            //If the paint tile indexes flag is set to true,
            //draw the index number on the tiles
            if(m_PaintTileIndexes == true)
            {
                m_Tiles[i]->paintIndex(i);
            }
		}
	}
    
	//Paint the Player
	if(m_Player != NULL)
	{
        //If paint tile scoring flag is set to true,
        //draw the path scoring
        if(m_PaintTileScoring == true)
        {
            //TODO: Paint the tile scores
        }
        
        //Paint the player
		m_Player->paint();
	}
}

void Level::reset()
{
	//Cycle through and reset all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->reset();
		}
	}
    
	//Reset the Player
	if(m_Player != NULL)
	{
		m_Player->reset();
        m_Player->setCurrentTile(m_Tiles[m_PlayerStartingTileIndex]);
	}
}

void Level::mouseLeftClickUpEvent(float aPositionX, float aPositionY)
{
	//Convert the mouse click position, into a tile index
	int index = getTileIndexForPosition(aPositionX, aPositionY);
    
	//Safety check that the tile isn't NULL
	if(m_Tiles[index] != NULL)
	{
        //Set the selected tile index
        setSelectedTileIndex(index);
        
        //If the tile is walkable, set the player's destination tile
        if(m_Tiles[index]->isWalkableTile() == true)
        {
            if(m_Player != NULL)
            {
                m_Player->setDestinationTile(m_Tiles[m_SelectedTileIndex]);
            }
        }
	}
}

void Level::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_R)
    {
        reset();
    }
    else if(keyCode == KEYCODE_S)
    {
        togglePaintTileScoring();
    }
    else if(keyCode == KEYCODE_I)
    {
        togglePaintTileIndexes();
    }
}

void Level::load(const char* levelName)
{
    //If the level name isn't NULL load the level from the filesystem,
    //if it is NULL load an empty level with just ground tiles
    if(levelName != NULL)
    {
        std::ifstream inputStream;
        
        inputStream.open(levelName,std::ifstream::in | std::ifstream::binary);
        
        if(inputStream.is_open() == true)
        {
            inputStream.seekg(0, inputStream.end);
            long long bufferSize = inputStream.tellg();
            
            inputStream.seekg(0,inputStream.beg);
            
            char* buffer = new char[bufferSize];
            
            inputStream.read(buffer, (int)bufferSize);
            
            inputStream.close();
            
            for (int i = 0; i < bufferSize ; i++)
            {
                setTileTypeAtIndex((TileType)buffer[i],i);
            }
            
            if(buffer != NULL)
            {
                delete[] buffer;
                buffer = NULL;
            }
            
        }
    }
    else
    {
        for( int i = 0; i < getNumberOfTiles(); i++)
        {
            setTileTypeAtIndex((TileType)(TileTypeGround),i);
        }
    }
    
    //The level is loaded, reset everything
    reset();
}

void Level::save(const char* levelName)
{
    //TODO: save the level
    //Create the buffer
    size_t bufferSize = getNumberOfTiles();
    char* buffer = new char[bufferSize];

    for (int i = 0; i < bufferSize ; i++)
    {
        buffer[i] = m_Tiles[i]->getTileType();
        
    }
    
    //File IO time
    std::ofstream outputStream;
    
    //Open the file
    outputStream.open(levelName, std::ofstream::out | std::ofstream::binary);
    
    //Did the file open?
    if(outputStream.is_open() == true)
    {
        //Write the buffer
        outputStream.write((char*)buffer, bufferSize);
        
        //Make sure to close the file stream
        outputStream.close();
    }
    else
    {
        //This may be a place where you could throw an exception in your game,
        //if you are opening a file for reading OR writing and it doesn't open.
    }
    if(buffer != NULL)
    {
        delete[] buffer;
        buffer = NULL;
        
    }
    
}

TileType Level::getTileTypeForIndex(int index)
{
    if(index >= 0 && index < getNumberOfTiles())
    {
        return m_Tiles[index]->getTileType();
    }
    return TileTypeUnknown;
}

unsigned int Level::getNumberOfTiles()
{
    return getNumberOfHorizontalTiles() * getNumberOfVerticalTiles();
}

unsigned int Level::getNumberOfHorizontalTiles()
{
	return m_HorizontalTiles;
}

unsigned int Level::getNumberOfVerticalTiles()
{
	return m_VerticalTiles;
}

bool Level::validateTileCoordinates(int aCoordinatesX, int aCoordinatesY)
{
    if(aCoordinatesX < 0 || aCoordinatesY < 0 || aCoordinatesX >= getNumberOfHorizontalTiles() || aCoordinatesY >= getNumberOfVerticalTiles())
	{
        return false;
    }
    return true;
}

int Level::getTileCoordinateForPosition(int aPosition)
{
	return (aPosition / m_TileSize);
}

int Level::getTileIndexForPosition(int aPositionX, int aPositionY)
{
	int coordinatesX = getTileCoordinateForPosition(aPositionX);
	int coordinatesY = getTileCoordinateForPosition(aPositionY);
	return getTileIndexForCoordinates(coordinatesX, coordinatesY);
}

int Level::getTileIndexForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	//Validate the coordinates, then calculate the array index
	if(validateTileCoordinates(aCoordinatesX, aCoordinatesY) == true)
	{
		return aCoordinatesX + (aCoordinatesY * getNumberOfHorizontalTiles());
	}
    
	return -1;
}

int Level::getTileIndexForTile(Tile* aTile)
{
	return getTileIndexForPosition(aTile->getX(), aTile->getY());
}

Tile* Level::getTileForPosition(int aPositionX, int aPositionY)
{
	return getTileForIndex(getTileIndexForPosition(aPositionX, aPositionY));
}

Tile* Level::getTileForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	return getTileForIndex(getTileIndexForCoordinates(aCoordinatesX, aCoordinatesY));
}

Tile* Level::getTileForIndex(int aIndex)
{
    //Safety check the index bounds
	if(aIndex >= 0 && aIndex < getNumberOfTiles())
	{
		return m_Tiles[aIndex];
	}
    
    //If we got here, it means the index passed in was out of bounds
	return NULL;
}

void Level::setTileTypeAtPosition(TileType tileType, int positionX, int positionY)
{
    setTileTypeAtIndex(tileType, getTileIndexForPosition(positionX, positionY));
}

void Level::setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY)
{
    setTileTypeAtIndex(tileType, getTileIndexForCoordinates(coordinatesX, coordinatesY));
}

void Level::setTileTypeAtIndex(TileType tileType, int index)
{
    //Safety check the index
    if(index >= 0 && index < getNumberOfTiles())
	{
        //Don't replace the tile if its the same type of tile that already exists
        if(m_Tiles[index] != NULL && m_Tiles[index]->getTileType() == tileType)
        {
            return;
        }
    
        //Delete the tile at the index, if one exists
        if(m_Tiles[index] != NULL)
        {
            delete m_Tiles[index];
            m_Tiles[index] = NULL;
        }
        
        //Create the new tile based on the TileType
        switch (tileType)
        {
            case TileTypeGround:
                m_Tiles[index] = new GroundTile();
                break;
			case TileTypeTree:
				m_Tiles[index] = new TreeTile();
				break;
			case TileTypeRock:
				m_Tiles[index] = new RockTile();
				break;
			case TileTypeWater:
				m_Tiles[index] = new WaterTile();
				break;
			case TileTypeGrass:
				m_Tiles[index] = new GrassTile();
				break;
			case TileTypePaved:
				m_Tiles[index] = new PavedTile();
				break;
            case TileTypeUnknown:
            default:
                m_Tiles[index] = NULL;
                break;
        }
        
        //Calculate the coordinates and set the tile position and size
        int coordinateX = (index % getNumberOfHorizontalTiles());
        int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());
        m_Tiles[index]->setPosition(coordinateX  * m_TileSize, coordinateY * m_TileSize);
        m_Tiles[index]->setSize(m_TileSize, m_TileSize);
	}
}

void Level::togglePaintTileScoring()
{
    m_PaintTileScoring = !m_PaintTileScoring;
}

void Level::togglePaintTileIndexes()
{
    m_PaintTileIndexes = !m_PaintTileIndexes;
}

void Level::setSelectedTileIndex(int aSelectedIndex)
{
	//Deselect the previously selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(false);
	}
    
	//Set the new tile index
	m_SelectedTileIndex = aSelectedIndex;
    
	//Selected the newly selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(true);
	}
}
void Level::Randomize()
{
    GDRandom random;
    random.randomizeSeed();
    
    for( int i = 0; i < getNumberOfTiles(); i++)
    {
        setTileTypeAtIndex((TileType)random.random(TileTypeCount),i);
    }
}
