#pragma once

#include "cocos2d.h"

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
#include "Menus/Title/TitleScreen.h"
#include "Menus/WorldMap/WorldMap.h"
#include "Objects/Isometric/IsometricDecorDeserializer.h"
#include "Objects/Isometric/IsometricObjectDeserializer.h"
#include "Objects/Platformer/PlatformerDecorDeserializer.h"
#include "Objects/Platformer/PlatformerObjectDeserializer.h"
#include "Scenes/Maps/Platformer/Backgrounds/BackgroundDeserializer.h"
#include "Scenes/Maps/Platformer/Terrain/CastleTerrainDeserializer.h"
#include "Scenes/Maps/Platformer/Weather/WeatherDeserializer.h"
#include "Sound/MusicDeserializer.h"

using namespace cocos2d;

class Bootstrapper 
{
public:
	static void initialize();
	static void shutDown();
};
