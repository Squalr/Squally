#include "EngineBootstrapper.h"

#include "platform/CCFileUtils.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Hackables/GlobalHackAttributeContainer.h"
#include "Engine/Input/Input.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Sound/SoundPool.h"
#include "Engine/UI/Mouse.h"

using namespace cocos2d;

void EngineBootstrapper::initialize()
{
	FileUtils::getInstance()->setWritablePath(FileUtils::getInstance()->getWritablePath());

	// Initialize global objects
	GlobalHackAttributeContainer::RegisterGlobalNode();
	DeveloperModeController::RegisterGlobalNode();
	GameCamera::RegisterGlobalNode();
	Input::RegisterGlobalNode();
	Mouse::RegisterGlobalNode();
	MusicPlayer::RegisterGlobalNode();
	SoundPool::RegisterGlobalNode();
}

void EngineBootstrapper::shutDown()
{
}
