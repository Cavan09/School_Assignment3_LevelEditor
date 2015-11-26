//Student: Cavan MacPhail
// Creation Date: Oct 30,2013
// Course Number: GAM1514
// Professor: Brad Flood
// Purpose: Editiing the Level

#include "LevelEditor.h"
#include "../Constants/Constants.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"
#include "../Menus/LevelSlotMenu.h"



LevelEditor::LevelEditor() :
    m_TilesMenu(NULL),
	m_LevelMenu(NULL),
    m_Level(NULL),
    m_IsMouseDown(false),
    m_SelectedTileIndex(-1)
{
    //Create the Tiles menu items
    m_TilesMenu = new UISideMenu(this, SideMenuRight);
    m_TilesMenu->addButton(new UIToggle("MenuTileGround"));
    m_TilesMenu->addButton(new UIToggle("MenuTileRock"));
    m_TilesMenu->addButton(new UIToggle("MenuTileTree"));
	m_TilesMenu->addButton(new UIToggle("MenuTileWater"));
	m_TilesMenu->addButton(new UIToggle("MenuTileGrass"));
	m_TilesMenu->addButton(new UIToggle("MenuTilePaved"));
    
    
    m_LevelMenu = new UISideMenu(this,SideMenuLeft);
    m_LevelMenu->addButton(new UIButton("Clear"));
    m_LevelMenu->addButton(new UIButton("Save"));
    m_LevelMenu->addButton(new UIButton("Load"));
    m_LevelMenu->addButton(new UIButton("Random"));
    m_LevelMenu->addButton(new UIButton("Exit"));
    
    //Create the level object
    m_Level = new Level(true);
    
    //Reset everything
    reset();
}

LevelEditor::~LevelEditor()
{
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
    
    if(m_TilesMenu != NULL)
    {
        delete m_TilesMenu;
        m_TilesMenu = NULL;
    }
	if(m_LevelMenu != NULL)
	{
		delete m_LevelMenu;
		m_LevelMenu = NULL;
	}
}

const char* LevelEditor::getName()
{
    return LEVEL_EDITOR_SCREEN_NAME;
}

void LevelEditor::update(double delta)
{
    if(m_Level != NULL)
    {
        m_Level->update(delta);
    }

    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->update(delta);
    }
	if(m_LevelMenu != NULL)
	{
		m_LevelMenu->update(delta);
	}

}

void LevelEditor::paint()
{
    if(m_Level != NULL)
    {
        m_Level->paint();
    }

    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->paint();
    }
	if(m_LevelMenu != NULL)
    {
        m_LevelMenu->paint();
    }
}

void LevelEditor::reset()
{
    if(m_Level != NULL)
    {
        m_Level->reset();
    }
}

void LevelEditor::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{    
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    if(m_LevelMenu != NULL)
    {
        m_LevelMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
    if(m_Level != NULL)
    {        
        if(m_SelectedTileIndex != -1 && m_IsMouseDown == true)
        {
            m_Level->setTileTypeAtPosition((TileType)m_SelectedTileIndex, positionX, positionY);
        }
    }
}

void LevelEditor::mouseLeftClickDownEvent(float positionX, float positionY)
{
    //Set the mouse down flag
    m_IsMouseDown = true;
}

void LevelEditor::mouseLeftClickUpEvent(float positionX, float positionY)
{
    //Set the mouse up flag
    m_IsMouseDown = false;
    
    //Safety check the level pointer, then set the new tile type in the index
    if(m_Level != NULL)
    {
        if(m_SelectedTileIndex != -1 && m_TilesMenu->isShowing() == false)
        {
            m_Level->setTileTypeAtPosition((TileType)m_SelectedTileIndex, positionX, positionY);
        }
    }
    
    //Notify the tiles menu of the mouse event
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseLeftClickUpEvent(positionX, positionY);
    }
    if(m_LevelMenu != NULL)
    {
        m_LevelMenu->mouseLeftClickUpEvent(positionX, positionY);
        m_LevelMenu->hide();
        m_TilesMenu->hide();
    }

}

void LevelEditor::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_TAB)
    {
        if(m_TilesMenu != NULL)
        {
            m_TilesMenu->isShowing() == true ? m_TilesMenu->hide() : m_TilesMenu->show();
        }
		if(m_LevelMenu != NULL)
		{
			m_LevelMenu->isShowing() == true ? m_LevelMenu->hide() : m_LevelMenu->show();
		}
    }
    else
    {
        if(m_Level != NULL)
        {
            m_Level->keyUpEvent(keyCode);
        }
    }
}

void LevelEditor::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{
    if(sideMenu == m_LevelMenu)
    {
        if(m_LevelMenu->getIndexForButton(button) == 0)
        {
            m_Level->load(NULL);
        }
        if(m_LevelMenu->getIndexForButton(button) == 1)
        {
            ((LevelSlotMenu*)ScreenManager::getInstance()->getScreenForName(LEVEL_SLOT_MENU_SCREEN_NAME))->setLoadSave(false);
            ((LevelSlotMenu*)ScreenManager::getInstance()->getScreenForName(LEVEL_SLOT_MENU_SCREEN_NAME))->setLevel(m_Level);
            ScreenManager::getInstance()->switchScreen(LEVEL_SLOT_MENU_SCREEN_NAME);
        }
        if(m_LevelMenu->getIndexForButton(button) == 2)
        {
            ((LevelSlotMenu*)ScreenManager::getInstance()->getScreenForName(LEVEL_SLOT_MENU_SCREEN_NAME))->setLoadSave(true);
			((LevelSlotMenu*)ScreenManager::getInstance()->getScreenForName(LEVEL_SLOT_MENU_SCREEN_NAME))->setLevel(m_Level);
            ScreenManager::getInstance()->switchScreen(LEVEL_SLOT_MENU_SCREEN_NAME);
        }
        if(m_LevelMenu->getIndexForButton(button) == 3)
        {
            m_Level->Randomize();
        }
        if(m_LevelMenu->getIndexForButton(button) == 4)
        {
			((LevelSlotMenu*)ScreenManager::getInstance()->getScreenForName(LEVEL_SLOT_MENU_SCREEN_NAME))->setLevel(m_Level = new Level());
            ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
        }
        
    }
}

void LevelEditor::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
{
    if(sideMenu == m_TilesMenu)
    {
        //Un-toggled the previously selected toggle
        UIToggle* previousToggle = (UIToggle*)m_TilesMenu->getButtonForIndex(m_SelectedTileIndex);
        if(previousToggle != NULL)
        {
            previousToggle->setIsToggled(false);
        }
    
        //Set the selected tile index
        m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
        
        //Hide the options and tiles menus
        m_TilesMenu->hide();
		m_LevelMenu->hide();
    }
}

