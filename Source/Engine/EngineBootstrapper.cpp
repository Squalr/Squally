#include "EngineBootstrapper.h"

void EngineBootstrapper::initialize()
{
	// Initialize global objects
	Analytics::registerGlobalNode();
	MouseState::registerGlobalNode();
	LayerDeserializer::registerGlobalNode();
}

void EngineBootstrapper::shutDown()
{
	Analytics::shutDown();
}
