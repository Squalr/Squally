#include "Bootstrapper.h"

#include "Engine/EngineBootstrapper.h"
#include "Entities/Isometric/IsometricEntityDeserializer.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"
#include "Menus/LoadingScreen/LoadingScreen.h"
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
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
