#include "EngineBootstrapper.h"

#include "Engine/Analytics/Analytics.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/CollisionEventDispatcher.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Localization/TranslationMenu.h"
#include "Engine/Maps/ObjectLayerDeserializer.h"
#include "Engine/Maps/Backgrounds/BackgroundDeserializer.h"
#include "Engine/Physics/CollisionDeserializer.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Mouse.h"

void EngineBootstrapper::initialize()
{
	// Initialize global objects
	Analytics::registerGlobalNode();
	BackgroundDeserializer::registerGlobalNode();
	TranslationMenu::registerGlobalNode();
	CollisionEventDispatcher::registerGlobalNode();
	DeveloperModeController::registerGlobalNode();
	GameCamera::registerGlobalNode();
	Input::registerGlobalNode();
	Mouse::registerGlobalNode();
	MouseState::registerGlobalNode();
	ObjectLayerDeserializer::registerGlobalNode();
	CollisionDeserializer::registerGlobalNode();
	SoundManager::registerGlobalNode();
}

void EngineBootstrapper::shutDown()
{
	Analytics::shutDown();
}
