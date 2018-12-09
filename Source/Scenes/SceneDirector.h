#pragma once

#include <stack>

#include "Engine/GlobalNode.h"

class TitleScreen;
class TakeOverMenu;
class HexusChapterSelectMenu;
class HexusDeckManagement;
class HexusRewardsMenu;
class HexusStoreMenu;
class HexusOpponentMenuCastle;
class HexusOpponentMenuCaverns;
class HexusOpponentMenuForest;
class HexusOpponentMenuIceCaps;
class HexusOpponentMenuJungle;
class HexusOpponentMenuMech;
class HexusOpponentMenuObelisk;
class HexusOpponentMenuRuins;
class HexusOpponentMenuTraining;
class HexusOpponentMenuVolcano;
class HexusPuzzlesMenu;
class WorldMap;
class LoadingScreen;
class IMap;
class OptionsMenu;
class ConfirmationMenu;
class Hexus;
class Cutscene;

namespace cocos2d
{
	class Scene;
	class EventCustom;
}

class SceneDirector : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	SceneDirector();
	~SceneDirector();

	void initializeListeners() override;
	void onGameNavigateNew(cocos2d::EventCustom* eventCustom);
	void onGameNavigateBack(cocos2d::EventCustom* eventCustom);
	void onGameNavigateConfirm(cocos2d::EventCustom* eventCustom);
	void onGameNavigateLoadCutscene(cocos2d::EventCustom* eventCustom);
	void onGameNavigateLoadLevel(cocos2d::EventCustom* eventCustom);
	void onGameNavigateEnterLevel(cocos2d::EventCustom* eventCustom);
	void onGameNavigateEnterCombat(cocos2d::EventCustom* eventCustom);

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

	std::stack<cocos2d::Scene*>* sceneHistory;

	static SceneDirector* instance;
};
