
#ifndef __GAM_1514_OSX_Game__LevelSlotMenu__
#define __GAM_1514_OSX_Game__LevelSlotMenu__

#include "Menu.h"
class Level;
class LevelEditor;
class OpenGLTexture;

class LevelSlotMenu : public Menu
{
public:
    LevelSlotMenu();
    ~LevelSlotMenu();
    
    const char* getName();
    bool getLoadSave();
    void setLoadSave(bool option);
    void setLevel(Level* level);
	void CheckingFiles(const char* file,const char* overlay, int i);
	void setGameLoad(bool game);
	Level* getLevel();

private:
    void buttonAction(UIButton* button);
    void addButton(UIButton* button,float x ,float y,int index);
    float m_XSpacing;
    float m_YSpacing;
    Level* m_Level;
    std::string m_LevelName;
    std::string m_OverLay;
    bool m_LoadSave;
	bool m_GameLoad;
};

#endif /* defined(__GAM_1514_OSX_Game__LevelSlotMenu__) */