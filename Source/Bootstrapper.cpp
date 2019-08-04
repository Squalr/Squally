#include "Bootstrapper.h"

#include "Engine/EngineBootstrapper.h"
#include "Menus/CursorSets.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionMapping.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	PlatformerCollisionMapping::registerGlobalNode();
	PlatformerItemDeserializer::registerGlobalNode();
	CursorSets::registerCursorSets();
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
