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
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterSelectMenu.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Castle/HexusOpponentMenuCastle.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Caverns/HexusOpponentMenuCaverns.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Forest/HexusOpponentMenuForest.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/IceCaps/HexusOpponentMenuIceCaps.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Jungle/HexusOpponentMenuJungle.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Mech/HexusOpponentMenuMech.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Obelisk/HexusOpponentMenuObelisk.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Ruins/HexusOpponentMenuRuins.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Training/HexusOpponentMenuTraining.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/Volcano/HexusOpponentMenuVolcano.h"
#include "Scenes/Menus/Minigames/Hexus/HexusDeckManagement.h"
#include "Scenes/Menus/Minigames/Hexus/Puzzles/HexusPuzzlesMenu.h"
#include "Scenes/Menus/Confirmation/ConfirmationMenu.h"
#include "Scenes/Menus/LoadingScreen/LoadingScreen.h"
#include "Scenes/Menus/Options/OptionsMenu.h"
#include "Scenes/Menus/Pause/PauseMenu.h"
#include "Scenes/Menus/SaveSelect/SaveSelectMenu.h"
#include "Scenes/Menus/WorldMap/WorldMap.h"
#include "Scenes/Menus/Title/TitleScreen.h"

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
	HexusChapterSelectMenu* hexusChapterSelectMenu;
	HexusDeckManagement* hexusDeckManagement;
	HexusOpponentMenuCastle* hexusOpponentMenuCastle;
	HexusOpponentMenuCaverns* hexusOpponentMenuCaverns;
	HexusOpponentMenuForest* hexusOpponentMenuForest;
	HexusOpponentMenuIceCaps* hexusOpponentMenuIceCaps;
	HexusOpponentMenuJungle* hexusOpponentMenuJungle;
	HexusOpponentMenuMech* hexusOpponentMenuMech;
	HexusOpponentMenuObelisk* hexusOpponentMenuObelisk;
	HexusOpponentMenuRuins* hexusOpponentMenuRuins;
	HexusOpponentMenuTraining* hexusOpponentMenuTraining;
	HexusOpponentMenuVolcano* hexusOpponentMenuVolcano;
	HexusPuzzlesMenu* hexusPuzzlesMenu;
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
