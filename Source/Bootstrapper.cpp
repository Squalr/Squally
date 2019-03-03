#include "Bootstrapper.h"

#include "Engine/EngineBootstrapper.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"
#include "Menus/CursorSets.h"
#include "Menus/LoadingScreen/LoadingScreen.h"
#include "Menus/MinigamesMenu.h"
#include "Menus/Options/OptionsScene.h"
#include "Menus/SaveSelect/SaveSelectMenu.h"
#include "Objects/Isometric/IsometricDecorDeserializer.h"
#include "Objects/Isometric/IsometricObjectDeserializer.h"
#include "Objects/Platformer/PlatformerDecorDeserializer.h"
#include "Objects/Platformer/PlatformerObjectDeserializer.h"
#include "Scenes/Hexus/Hexus.h"
#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterSelectMenu.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Castle/HexusOpponentMenuCastle.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Caverns/HexusOpponentMenuCaverns.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Forest/HexusOpponentMenuForest.h"
#include "Scenes/Hexus/Menus/OpponentSelect/IceCaps/HexusOpponentMenuIceCaps.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Jungle/HexusOpponentMenuJungle.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Mech/HexusOpponentMenuMech.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Obelisk/HexusOpponentMenuObelisk.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Ruins/HexusOpponentMenuRuins.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Training/HexusOpponentMenuTraining.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Volcano/HexusOpponentMenuVolcano.h"
#include "Scenes/Hexus/Menus/HexusDeckManagement.h"
#include "Scenes/Hexus/Menus/HexusRewardsMenu.h"
#include "Scenes/Hexus/Menus/Puzzles/HexusPuzzlesMenu.h"
#include "Scenes/Hexus/Menus/Store/HexusStoreMenu.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Physics/PhysicsDeserializer.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionMapping.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Terrain/CastleTerrainDeserializer.h"
#include "Scenes/Platformer/Level/Weather/WeatherDeserializer.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Platformer/WorldMap/WorldMap.h"
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

	// Inventory deserializers
	PlatformerItemDeserializer::registerGlobalNode();

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
	PhysicsDeserializer::registerGlobalNode();

	CastleTerrainDeserializer::registerGlobalNode();
	MusicDeserializer::registerGlobalNode();
	PlatformerCollisionMapping::registerGlobalNode();

	CursorSets::registerCursorSets();
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
