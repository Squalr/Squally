#include "EngineBootstrapper.h"

void EngineBootstrapper::initialize()
{
	// Initialize global objects
	Analytics::registerGlobalNode();
	GameCamera::registerGlobalNode();
	Input::registerGlobalNode();
	MouseState::registerGlobalNode();
	ObjectLayerDeserializer::registerGlobalNode();
	CollisionDeserializer::registerGlobalNode();
}

void EngineBootstrapper::shutDown()
{
	Analytics::shutDown();
}
