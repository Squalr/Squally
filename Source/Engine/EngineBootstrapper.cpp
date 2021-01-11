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
	Analytics::RegisterGlobalNode();
	GlobalHackAttributeContainer::RegisterGlobalNode();
	DeveloperModeController::RegisterGlobalNode();
	GameCamera::RegisterGlobalNode();
	Input::RegisterGlobalNode();
	Mouse::RegisterGlobalNode();
	MusicPlayer::RegisterGlobalNode();
}

void EngineBootstrapper::shutDown()
{
	Analytics::shutDown();
}
