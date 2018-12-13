#include "EngineBootstrapper.h"

#include "Engine/Analytics/Analytics.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Maps/ObjectLayerDeserializer.h"
#include "Engine/Physics/CollisionDeserializer.h"

void EngineBootstrapper::initialize()
{
	// Initialize global objects
	Analytics::registerGlobalNode();
	DeveloperModeController::registerGlobalNode();
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
