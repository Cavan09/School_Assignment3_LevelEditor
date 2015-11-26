//
//  MainMenu.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "MainMenu.h"
#include "LevelSlotMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"


MainMenu::MainMenu() : Menu(NULL, NULL)
{
    addButton(new UIButton("ButtonLoadLevel"));
    addButton(new UIButton("ButtonLevelEditor"));
    addButton(new UIButton("ButtonExit"));
}

MainMenu::~MainMenu()
{

}

const char* MainMenu::getName()
{
    return MAIN_MENU_SCREEN_NAME;
}

void MainMenu::buttonAction(UIButton* button)
{
    int index = getIndexForButton(button);
    if(index == 0)
    {
		((LevelSlotMenu*)ScreenManager::getInstance()->getScreenForName(LEVEL_SLOT_MENU_SCREEN_NAME))->setLoadSave(true);
		((LevelSlotMenu*)ScreenManager::getInstance()->getScreenForName(LEVEL_SLOT_MENU_SCREEN_NAME))->setGameLoad(true);
        ScreenManager::getInstance()->switchScreen(LEVEL_SLOT_MENU_SCREEN_NAME);
    }
    else if(index == 1)
    {
        ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
    }
    else if (index == 2)
    {
        exit(1);
    }
}
