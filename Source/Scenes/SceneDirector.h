#pragma once
#include "cocos2d.h"

#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/HexusEvents.h"
#include "Events/NavigationEvents.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterSelectMenu.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Castle/HexusOpponentMenuCastle.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Caverns/HexusOpponentMenuCaverns.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Forest/HexusOpponentMenuForest.h"
#include "Menus/Minigames/Hexus/OpponentSelect/IceCaps/HexusOpponentMenuIceCaps.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Jungle/HexusOpponentMenuJungle.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Mech/HexusOpponentMenuMech.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Obelisk/HexusOpponentMenuObelisk.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Ruins/HexusOpponentMenuRuins.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Training/HexusOpponentMenuTraining.h"
#include "Menus/Minigames/Hexus/OpponentSelect/Volcano/HexusOpponentMenuVolcano.h"
#include "Menus/Minigames/Hexus/HexusDeckManagement.h"
#include "Menus/Minigames/Hexus/HexusRewardsMenu.h"
#include "Menus/Minigames/Hexus/Puzzles/HexusPuzzlesMenu.h"
#include "Menus/Minigames/Hexus/Store/HexusStoreMenu.h"
#include "Menus/Minigames/MinigamesMenu.h"
#include "Menus/LoadingScreen/LoadingScreen.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Menus/SaveSelect/SaveSelectMenu.h"
#include "Menus/TakeOverMenu.h"
#include "Menus/Title/TitleScreen.h"
#include "Menus/WorldMap/WorldMap.h"
#include "Scenes/Maps/IMap.h"
#include "Scenes/Maps/Isometric/IsometricMap.h"
#include "Scenes/Maps/Platformer/CombatMap.h"
#include "Scenes/Maps/Platformer/PlatformerMap.h"
#include "Scenes/Hexus/Hexus.h"

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
	void onGameNavigateEnterCombat(EventCustom* eventCustom);

	TitleScreen* titleScreen;
	TakeOverMenu* saveSelectMenu;
	TakeOverMenu* minigamesMenu;
	HexusChapterSelectMenu* hexusChapterSelectMenu;
	HexusDeckManagement* hexusDeckManagement;
	HexusRewardsMenu* hexusRewardsMenu;
	HexusStoreMenu* hexusStoreMenu;
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
	LoadingScreen* innerLoadingScreen;
	TakeOverMenu* loadingScreen;
	IMap* map;
	IMap* combatMap;
	OptionsMenu* innerOptionsMenu;
	TakeOverMenu* optionsMenu;
	TakeOverMenu* pauseMenu;
	ConfirmationMenu* innerConfirmationMenu;
	TakeOverMenu* confirmationMenu;
	Hexus* hexus;
	Cutscene* cutscene;

	std::stack<Scene*>* sceneHistory;

	static SceneDirector* instance;
};
