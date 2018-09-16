#include "EngineBootstrapper.h"

void EngineBootstrapper::initialize()
{
	// Initialize global event listeners
	MouseState::registerGlobalNode();
}
