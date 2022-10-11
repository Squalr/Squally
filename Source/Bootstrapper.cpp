#include "Bootstrapper.h"

#include "Engine/EngineBootstrapper.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Menus/CursorSets.h"
#include "Music/TrackDeserializer.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionMapping.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	PlatformerCollisionMapping::RegisterGlobalNode();
	PlatformerItemDeserializer::RegisterGlobalNode();
	TrackDeserializer::RegisterGlobalNode();
	CursorSets::RegisterCursorSets();
	StatsTables::RegisterGlobalNode();
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
