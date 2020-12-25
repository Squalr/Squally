#include "EngineBootstrapper.h"

#include "cocos/platform/CCFileUtils.h"

#include "Engine/Analytics/Analytics.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Hackables/GlobalHackAttributeContainer.h"
#include "Engine/Input/Input.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/UI/Mouse.h"

using namespace cocos2d;

void EngineBootstrapper::initialize()
{
	FileUtils::getInstance()->setWritablePath(FileUtils::getInstance()->getWritablePath());

	// Initialize global objects
	Analytics::registerGlobalNode();
	GlobalHackAttributeContainer::registerGlobalNode();
	DeveloperModeController::registerGlobalNode();
	GameCamera::registerGlobalNode();
	Input::registerGlobalNode();
	Mouse::registerGlobalNode();
	MusicPlayer::registerGlobalNode();
}

void EngineBootstrapper::shutDown()
{
	Analytics::shutDown();
}
