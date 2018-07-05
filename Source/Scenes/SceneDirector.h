#pragma once
#include "cocos2d.h"

#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/HexusEvents.h"
#include "Events/NavigationEvents.h"
#include "Fight/Fight.h"
#include "Level/Level.h"
#include "Minigames/Minigames.h"
#include "Resources.h"
#include "Scenes/Menus/Confirmation/ConfirmationMenu.h"
#include "Scenes/Menus/LoadingScreen/LoadingScreen.h"
#include "Scenes/Menus/Options/OptionsMenu.h"
#include "Scenes/Menus/Pause/PauseMenu.h"
#include "Scenes/Menus/Story/StoryMap.h"
#include "Scenes/Menus/Title/TitleScreen.h"
#include "Scenes/Menus/Tutorial/TutorialScreen.h"

using namespace cocos2d;

class SceneDirector : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	SceneDirector();
	~SceneDirector();

	void onGameNavigateNew(EventCustom* eventCustom);
	void onGameNavigateBack(EventCustom* eventCustom);
	void onGameNavigateConfirm(EventCustom* eventCustom);
	void onGameNavigateLoadLevel(EventCustom* eventCustom);
	void onGameNavigateEnterLevel(EventCustom* eventCustom);
	void onGameNavigateFight(EventCustom* eventCustom);
	void initializeEventListeners() override;

	TitleScreen* titleScreen;
	TutorialScreen* tutorialScreen;
	StoryMap* storyMap;
	LoadingScreen* loadingScreen;
	Level* level;
	Fight* fight;
	OptionsMenu* optionsMenu;
	PauseMenu* pauseMenu;
	ConfirmationMenu* confirmationMenu;
	Hexus* hexus;

	std::stack<Scene*>* sceneHistory;

	static SceneDirector* instance;
};
