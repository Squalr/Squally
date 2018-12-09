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
#include "Entities/Platformer/PlatformerCollisionMapping.h"
#include "Entities/Platformer/SquallyDeserializer.h"
#include "Objects/Isometric/IsometricDecorDeserializer.h"
#include "Objects/Isometric/IsometricObjectDeserializer.h"
#include "Objects/Platformer/PlatformerDecorDeserializer.h"
#include "Objects/Platformer/PlatformerObjectDeserializer.h"
#include "Scenes/Maps/Platformer/Backgrounds/BackgroundDeserializer.h"
#include "Scenes/Maps/Platformer/Terrain/CastleTerrainDeserializer.h"
#include "Scenes/Maps/Platformer/Weather/WeatherDeserializer.h"
#include "Scenes/SceneDirector.h"
#include "Sound/MusicDeserializer.h"

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	SceneDirector::registerGlobalNode();
	PlatformerCollisionMapping::registerGlobalNode();

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
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
