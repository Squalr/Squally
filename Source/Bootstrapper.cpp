#include "Bootstrapper.h"

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	// Register scenes
	SceneDirector::registerGlobalNode();
	TitleScreen::registerGlobalScene();
	WorldMap::registerGlobalScene();

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
