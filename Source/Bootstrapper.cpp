#include "Bootstrapper.h"

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
