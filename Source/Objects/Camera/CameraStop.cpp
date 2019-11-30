#include "CameraStop.h"

#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string CameraStop::MapKeyCameraStop = "camera-stop";

CameraStop* CameraStop::create(ValueMap& properties)
{
	CameraStop* instance = new CameraStop(properties);

	instance->autorelease();

	return instance;
}

CameraStop::CameraStop(ValueMap& properties) : GameObject(properties)
{
}

CameraStop::~CameraStop()
{
}

void CameraStop::update(float dt)
{
	super::update(dt);

	// GameCamera::getInstance();
}
