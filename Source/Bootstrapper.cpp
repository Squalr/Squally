#include "Bootstrapper.h"

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	// Start scene director
	SceneDirector::registerGlobalNode();

	// Initialize global event listeners
	PlatformerCollisionMapping::registerGlobalNode();
}
