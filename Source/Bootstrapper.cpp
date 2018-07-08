#include "Bootstrapper.h"

void Bootstrapper::initialize()
{
	// Start scene director
	SceneDirector::registerGlobalNode();

	// Initialize global event listeners
	PlatformerCollisionMapping::registerGlobalNode();
}
