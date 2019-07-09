#include "Bootstrapper.h"

#include "Engine/EngineBootstrapper.h"
#include "Menus/CursorSets.h"

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	CursorSets::registerCursorSets();
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
