#include "Bootstrapper.h"

#include "Engine/EngineBootstrapper.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"
#include "Menus/CursorSets.h"
#include "Menus/LoadingScreen/LoadingScreen.h"
#include "Menus/Hexus/ChapterSelect/HexusChapterSelectMenu.h"
#include "Menus/Hexus/OpponentSelect/Castle/HexusOpponentMenuCastle.h"
#include "Menus/Hexus/OpponentSelect/Caverns/HexusOpponentMenuCaverns.h"
#include "Menus/Hexus/OpponentSelect/Forest/HexusOpponentMenuForest.h"
#include "Menus/Hexus/OpponentSelect/IceCaps/HexusOpponentMenuIceCaps.h"
#include "Menus/Hexus/OpponentSelect/Jungle/HexusOpponentMenuJungle.h"
#include "Menus/Hexus/OpponentSelect/Mech/HexusOpponentMenuMech.h"
#include "Menus/Hexus/OpponentSelect/Obelisk/HexusOpponentMenuObelisk.h"
#include "Menus/Hexus/OpponentSelect/Ruins/HexusOpponentMenuRuins.h"
#include "Menus/Hexus/OpponentSelect/Training/HexusOpponentMenuTraining.h"
#include "Menus/Hexus/OpponentSelect/Volcano/HexusOpponentMenuVolcano.h"
#include "Menus/Hexus/HexusDeckManagement.h"
#include "Menus/Hexus/HexusRewardsMenu.h"
#include "Menus/Hexus/Puzzles/HexusPuzzlesMenu.h"
#include "Menus/Hexus/Store/HexusStoreMenu.h"
#include "Menus/MinigamesMenu.h"
#include "Menus/Options/OptionsScene.h"
#include "Menus/Title/TitleScreen.h"
#include "Menus/SaveSelect/SaveSelectMenu.h"
#include "Menus/WorldMap/WorldMap.h"
#include "Objects/Isometric/IsometricDecorDeserializer.h"
#include "Objects/Isometric/IsometricObjectDeserializer.h"
#include "Objects/Platformer/PlatformerDecorDeserializer.h"
#include "Objects/Platformer/PlatformerObjectDeserializer.h"
#include "Scenes/Hexus/Hexus.h"
#include "Scenes/Maps/Platformer/CombatMap.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionMapping.h"
#include "Scenes/Maps/Platformer/PlatformerMap.h"
#include "Scenes/Maps/Platformer/Terrain/CastleTerrainDeserializer.h"
#include "Scenes/Maps/Platformer/Weather/WeatherDeserializer.h"
#include "Sound/MusicDeserializer.h"

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	// Register scenes
	CombatMap::registerGlobalScene();
	PlatformerMap::registerGlobalScene();
	LoadingScreen::registerGlobalScene();
	Hexus::registerGlobalScene();
	HexusChapterSelectMenu::registerGlobalScene();
	HexusOpponentMenuCastle::registerGlobalScene();
	HexusOpponentMenuCaverns::registerGlobalScene();
	HexusOpponentMenuForest::registerGlobalScene();
	HexusOpponentMenuIceCaps::registerGlobalScene();
	HexusOpponentMenuJungle::registerGlobalScene();
	HexusOpponentMenuMech::registerGlobalScene();
	HexusOpponentMenuObelisk::registerGlobalScene();
	HexusOpponentMenuRuins::registerGlobalScene();
	HexusOpponentMenuTraining::registerGlobalScene();
	HexusOpponentMenuVolcano::registerGlobalScene();
	HexusDeckManagement::registerGlobalScene();
	HexusRewardsMenu::registerGlobalScene();
	HexusPuzzlesMenu::registerGlobalScene();
	HexusStoreMenu::registerGlobalScene();
	MinigamesMenu::registerGlobalScene();
	OptionsScene::registerGlobalScene();
	TitleScreen::registerGlobalScene();
	WorldMap::registerGlobalScene();
	SaveSelectMenu::registerGlobalScene();

	// Entity deserializers
	PlatformerEntityDeserializer::registerGlobalNode();
	PlatformerCollisionMapping::registerGlobalNode();

	// Decor deserializers
	IsometricDecorDeserializer::registerGlobalNode();
	IsometricObjectDeserializer::registerGlobalNode();

	// Object deserializers
	PlatformerDecorDeserializer::registerGlobalNode();
	PlatformerObjectDeserializer::registerGlobalNode();

	// Environment deserializers
	WeatherDeserializer::registerGlobalNode();

	CastleTerrainDeserializer::registerGlobalNode();
	MusicDeserializer::registerGlobalNode();
	PlatformerCollisionMapping::registerGlobalNode();

	CursorSets::registerCursorSets();
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
