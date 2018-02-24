#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Menus/Title/TitleScreen.h"
#include "GUI/Menus/Tutorial/TutorialScreen.h"
#include "GUI/Menus/Story/StoryMap.h"
#include "GUI/Menus/Options/OptionsMenu.h"
#include "GUI/Menus/Pause/PauseMenu.h"
#include "GUI/Menus/Confirmation/ConfirmationMenu.h"
#include "Level/Level.h"
#include "Minigames/Minigames.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class Game : public Node
{
public:
	static Game * create();

private:
	Game();
	~Game();

	void onGameNavigateNew(EventCustom* eventCustom);
	void onGameNavigateBack(EventCustom* eventCustom);
	void onGameNavigateConfirm(EventCustom* eventCustom);
	void onGameNavigateNewLevel(EventCustom* eventCustom);
	void loadScene(Scene* scene);
	void initializeEventListeners();

	TitleScreen* titleScreen;
	TutorialScreen* tutorialScreen;
	StoryMap* storyMap;
	Level* level;
	OptionsMenu* optionsMenu;
	PauseMenu* pauseMenu;
	ConfirmationMenu* confirmationMenu;
	Hexium* hexium;

	std::stack<Scene*>* sceneHistory;
};
