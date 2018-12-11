#include "Bootstrapper.h"

#include "Engine/EngineBootstrapper.h"
#include "Entities/Isometric/IsometricEntityDeserializer.h"
#include "Entities/Platformer/Enemies/Castle/CastleEnemyDeserializer.h"
#include "Entities/Platformer/Enemies/Caverns/CavernsEnemyDeserializer.h"
#include "Entities/Platformer/Enemies/Forest/ForestEnemyDeserializer.h"
#include "Entities/Platformer/Enemies/Jungle/JungleEnemyDeserializer.h"
#include "Entities/Platformer/Enemies/Mech/MechEnemyDeserializer.h"
#include "Entities/Platformer/Enemies/Obelisk/ObeliskEnemyDeserializer.h"
#include "Entities/Platformer/Enemies/Ruins/RuinsEnemyDeserializer.h"
#include "Entities/Platformer/Enemies/Snow/SnowEnemyDeserializer.h"
#include "Entities/Platformer/Enemies/Volcano/VolcanoEnemyDeserializer.h"
#include "Entities/Platformer/Npcs/Castle/CastleNpcDeserializer.h"
#include "Entities/Platformer/Npcs/Caverns/CavernsNpcDeserializer.h"
#include "Entities/Platformer/Npcs/Forest/ForestNpcDeserializer.h"
#include "Entities/Platformer/Npcs/Jungle/JungleNpcDeserializer.h"
#include "Entities/Platformer/Npcs/Mech/MechNpcDeserializer.h"
#include "Entities/Platformer/Npcs/Obelisk/ObeliskNpcDeserializer.h"
#include "Entities/Platformer/Npcs/Ruins/RuinsNpcDeserializer.h"
#include "Entities/Platformer/Npcs/Snow/SnowNpcDeserializer.h"
#include "Entities/Platformer/Npcs/Volcano/VolcanoNpcDeserializer.h"
#include "Entities/Platformer/SquallyDeserializer.h"
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
#include "Scenes/Maps/Platformer/Backgrounds/BackgroundDeserializer.h"
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
	SquallyDeserializer::registerGlobalNode();
	IsometricEntityDeserializer::registerGlobalNode();
	CastleEnemyDeserializer::registerGlobalNode();
	CavernsEnemyDeserializer::registerGlobalNode();
	ForestEnemyDeserializer::registerGlobalNode();
	JungleEnemyDeserializer::registerGlobalNode();
	MechEnemyDeserializer::registerGlobalNode();
	ObeliskEnemyDeserializer::registerGlobalNode();
	RuinsEnemyDeserializer::registerGlobalNode();
	SnowEnemyDeserializer::registerGlobalNode();
	VolcanoEnemyDeserializer::registerGlobalNode();
	CastleNpcDeserializer::registerGlobalNode();
	CavernsNpcDeserializer::registerGlobalNode();
	ForestNpcDeserializer::registerGlobalNode();
	JungleNpcDeserializer::registerGlobalNode();
	MechNpcDeserializer::registerGlobalNode();
	RuinsNpcDeserializer::registerGlobalNode();
	SnowNpcDeserializer::registerGlobalNode();
	ObeliskNpcDeserializer::registerGlobalNode();
	VolcanoNpcDeserializer::registerGlobalNode();
	PlatformerCollisionMapping::registerGlobalNode();

	// Decor deserializers
	IsometricDecorDeserializer::registerGlobalNode();
	IsometricObjectDeserializer::registerGlobalNode();

	// Object deserializers
	PlatformerDecorDeserializer::registerGlobalNode();
	PlatformerObjectDeserializer::registerGlobalNode();

	// Environment deserializers
	BackgroundDeserializer::registerGlobalNode();
	WeatherDeserializer::registerGlobalNode();

	CastleTerrainDeserializer::registerGlobalNode();
	MusicDeserializer::registerGlobalNode();
	PlatformerCollisionMapping::registerGlobalNode();
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
