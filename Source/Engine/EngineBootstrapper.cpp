#include "EngineBootstrapper.h"

void EngineBootstrapper::initialize()
{
	// Initialize global objects
	Analytics::registerGlobalNode();
	Input::registerGlobalNode();
	MouseState::registerGlobalNode();
	ObjectLayerDeserializer::registerGlobalNode();
	CollisionDeserializer::registerGlobalNode();
	TerrainDeserializer::registerGlobalNode();
}

void EngineBootstrapper::shutDown()
{
	Analytics::shutDown();
}
