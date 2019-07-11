#include "Bootstrapper.h"

#include "Engine/EngineBootstrapper.h"
#include "Menus/CursorSets.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionMapping.h"

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	PlatformerCollisionMapping::registerGlobalNode();
	CursorSets::registerCursorSets();
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
