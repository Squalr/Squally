#include "Bootstrapper.h"

#include "cocos2d.h"

#include "Engine/EngineBootstrapper.h"
#include "Entities/Platformer/PlatformerCollisionMapping.h"
#include "Scenes/SceneDirector.h"

using namespace cocos2d;

void Bootstrapper::initialize()
{
	EngineBootstrapper::initialize();

	// Start scene director
	SceneDirector::registerGlobalNode();

	// Initialize global event listeners
	PlatformerCollisionMapping::registerGlobalNode();
}

void Bootstrapper::shutDown()
{
	EngineBootstrapper::shutDown();
}
