#include "CameraFocus.h"

#include "Engine/Camera/GameCamera.h"

const std::string CameraFocus::MapKeyCameraFocus = "camera-focus";

CameraFocus* CameraFocus::create(ValueMap* initProperties)
{
	CameraFocus* instance = new CameraFocus(initProperties);

	instance->autorelease();

	return instance;
}

CameraFocus::CameraFocus(ValueMap* initProperties) : SerializableObject(initProperties)
{
}

CameraFocus::~CameraFocus()
{
}

void CameraFocus::onEnter()
{
	SerializableObject::onEnter();

	GameCamera::getInstance()->setTarget(this);
}
