//Student: Cavan MacPhail
// Creation Date: Oct 30,2013
// Course Number: GAM1514
// Professor: Brad Flood
// Purpose: Menu for saveing and loading as well as the logic


#include "LevelSlotMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Game/Level.h"
#include "../Level Editor/LevelEditor.h"
#include <stdlib.h>
#include <fstream>


LevelSlotMenu::LevelSlotMenu() : Menu(NULL, NULL),
    m_XSpacing(0),
    m_YSpacing(0),
    m_Level(NULL),
    m_LevelName(LEVEL_NAME),
    m_LoadSave(false),
    m_OverLay(OVERLAY_TEXTURE),
	m_GameLoad(NULL)
{
    m_XSpacing = SLOT_BUTTON_X_PERCENTAGE;
    m_YSpacing = SLOT_BUTTON_Y_PERCENTAGE;
    int index = 0;
	m_Level = new Level(false);
    for ( int i = 0; i < BUTTON_COLOUMNS ; i++)
    {
    
        for(int j = 0; j < BUTTON_ROWS; j++)
        {
            
            addButton(new UIButton(m_OverLay.c_str(),m_OverLay.c_str()), m_XSpacing, m_YSpacing,index);
            m_YSpacing += SLOT_BUTTON_Y_PERCENTAGE;
            index++;
        }
        m_XSpacing += SLOT_BUTTON_X_PERCENTAGE;
        m_YSpacing = SLOT_BUTTON_Y_PERCENTAGE;
    }
	CheckingFiles(LEVEL_SLOT_1,SAVE_IMAGE_1,0);
	CheckingFiles(LEVEL_SLOT_2,SAVE_IMAGE_2,1);
	CheckingFiles(LEVEL_SLOT_3,SAVE_IMAGE_3,2);
	CheckingFiles(LEVEL_SLOT_4,SAVE_IMAGE_4,3);
	CheckingFiles(LEVEL_SLOT_5,SAVE_IMAGE_5,4);
	CheckingFiles(LEVEL_SLOT_6,SAVE_IMAGE_6,5);
}

LevelSlotMenu::~LevelSlotMenu()
{
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
	
}

const char* LevelSlotMenu::getName()
{
    return LEVEL_SLOT_MENU_SCREEN_NAME;
}

void LevelSlotMenu::buttonAction(UIButton* button)
{
    
    m_OverLay = OVERLAY_TEXTURE;
    m_LevelName = LEVEL_NAME;
    int index = getIndexForButton(button);
    if(index == 0)
    {
        m_LevelName.append("1");
        m_OverLay.append("1"); 
    }
    else if(index == 1)
    {
        m_LevelName.append("2");
        m_OverLay.append("2");
    }
    else if(index == 2)
    {
        m_LevelName.append("3");
        m_OverLay.append("3");
    }
    else if(index == 3)
    {
        m_LevelName.append("4");
        m_OverLay.append("4");
    }
    else if(index == 4)
    {
        m_LevelName.append("5");
        m_OverLay.append("5");
    }
    else if(index == 5)
    {
        m_LevelName.append("6");
        m_OverLay.append("6");
    }
	if(m_LoadSave == false)
    {
        m_Level->save(m_LevelName.c_str());
        m_Buttons.at(index)->swapOverlay(m_OverLay.c_str());
    }
    else if(m_LoadSave == true)
    {
		std::ifstream filename(m_LevelName.c_str());
		if(!filename)
		{
			m_Level->load(NULL);
		}
		else
		{
			m_Level->load(m_LevelName.c_str());
		}
    }
	if(m_GameLoad == true)
	{
		((Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))->setLevel(m_Level);
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
	}
	else
	{
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
	}
}
void LevelSlotMenu::addButton(UIButton* button,float x ,float y,int index)
{
    if(button != NULL)
    {
        int index = m_Buttons.size();
        
        button->setListener(this);
        
        if(index == 0)
        {
            m_SelectedIndex = 0;
        }
        else if(index == 1 && m_ShowBack == true)
        {
            m_Buttons.at(m_SelectedIndex)->setIsSelected(false);
            button->setIsSelected(true);
            m_SelectedIndex = 1;
        }

        m_Buttons.push_back(button);
        m_Buttons.at(index)->setCenterPosition(getWidth() * x,getHeight() * y);
    
    }
}
bool LevelSlotMenu::getLoadSave()
{
    return m_LoadSave;
}
void LevelSlotMenu::setLoadSave(bool option)
{
    m_LoadSave = option;
}
void LevelSlotMenu::setLevel(Level* level)
{
    m_Level = level;
}
void LevelSlotMenu::setGameLoad(bool game)
{
	m_GameLoad = game;
}
Level* LevelSlotMenu::getLevel()
{
	return m_Level;
}
void LevelSlotMenu::CheckingFiles(const char* file,const char* overlay, int i)
{
	std::ifstream filename(file);
	if(!filename)
	{
		
	}
	else
	{
		m_Buttons.at(i)->swapOverlay(overlay);
	}
}