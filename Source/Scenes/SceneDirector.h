#pragma once
#include "cocos2d.h"

#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/HexusEvents.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Maps/IMap.h"
#include "Scenes/Maps/Isometric/IsometricMap.h"
#include "Scenes/Maps/Platformer/PlatformerMap.h"
#include "Resources.h"
#include "Scenes/Fights/Fight.h"
#include "Scenes/Hexus/Hexus.h"
#include "Scenes/Menus/Minigames/MinigamesMenu.h"
#include "Scenes/Menus/Minigames/Hexus/HexusMenu.h"
#include "Scenes/Menus/Minigames/Hexus/HexusPuzzlesMenu.h"
#include "Scenes/Menus/Confirmation/ConfirmationMenu.h"
#include "Scenes/Menus/LoadingScreen/LoadingScreen.h"
#include "Scenes/Menus/Options/OptionsMenu.h"
#include "Scenes/Menus/Pause/PauseMenu.h"
#include "Scenes/Menus/SaveSelect/SaveSelectMenu.h"
#include "Scenes/Menus/WorldMap/WorldMap.h"
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

	void initializeListeners() override;
	void onGameNavigateNew(EventCustom* eventCustom);
	void onGameNavigateBack(EventCustom* eventCustom);
	void onGameNavigateConfirm(EventCustom* eventCustom);
	void onGameNavigateLoadCutscene(EventCustom* eventCustom);
	void onGameNavigateLoadLevel(EventCustom* eventCustom);
	void onGameNavigateEnterLevel(EventCustom* eventCustom);
	void onGameNavigateFight(EventCustom* eventCustom);

	TitleScreen* titleScreen;
	SaveSelectMenu* saveSelectMenu;
	MinigamesMenu* minigamesMenu;
	HexusMenu* hexusMenu;
	HexusPuzzlesMenu* hexusPuzzlesMenu;
	TutorialScreen* tutorialScreen;
	WorldMap* worldMap;
	LoadingScreen* loadingScreen;
	IMap* map;
	Fight* fight;
	OptionsMenu* optionsMenu;
	PauseMenu* pauseMenu;
	ConfirmationMenu* confirmationMenu;
	Hexus* hexus;
	Cutscene* cutscene;

	std::stack<Scene*>* sceneHistory;

	static SceneDirector* instance;
};
