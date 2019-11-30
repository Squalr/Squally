#include "CameraStop.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
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
	this->debugDraw = DrawNode::create();
	this->stopSize = Size(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(32.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(32.0f)).asFloat()
	);

	this->debugDraw->drawSolidRect(-Vec2(this->stopSize / 2.0f), Vec2(this->stopSize / 2.0f), Color4F::GREEN);

	this->addChild(this->debugDraw);
}

CameraStop::~CameraStop()
{
}

void CameraStop::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CameraStop::update(float dt)
{
	super::update(dt);

	Vec2 thisCoords = GameUtils::getWorldCoords(this);
	Vec2 cameraCoords = GameCamera::getInstance()->getCameraPosition();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 cameraDistance = thisCoords - cameraCoords;
	Vec2 cameraInset = Vec2(visibleSize / 2.0f) - (thisCoords - cameraCoords);
	
	float distL = cameraDistance.x - this->stopSize.width / 2.0f;
	float distR = cameraDistance.x + this->stopSize.width / 2.0f;
	float distT = cameraDistance.y - this->stopSize.height / 2.0f;
	float distB = cameraDistance.y + this->stopSize.height / 2.0f;

	if ((distL <= visibleSize.width / 2.0f && distR >= -visibleSize.width / 2.0f) &&
		(distT <= visibleSize.height / 2.0f && distB >= -visibleSize.height / 2.0f))
	{
		if (cameraInset.x < cameraInset.y)
		{
			if (std::abs(distL) < std::abs(distR))
			{
				GameCamera::getInstance()->setCameraPosition(Vec2(cameraCoords.x - cameraInset.x - this->stopSize.width / 2.0f, cameraCoords.y));
			}
			else
			{
				GameCamera::getInstance()->setCameraPosition(Vec2(cameraCoords.x - cameraInset.x + this->stopSize.width / 2.0f, cameraCoords.y));
			}
		}
		else
		{
			if (std::abs(distT) < std::abs(distB))
			{
				GameCamera::getInstance()->setCameraPosition(Vec2(cameraCoords.x, cameraCoords.y - cameraInset.y - this->stopSize.height / 2.0f));
			}
			else
			{
				GameCamera::getInstance()->setCameraPosition(Vec2(cameraCoords.x, cameraCoords.y - cameraInset.y + this->stopSize.height / 2.0f));
			}
		}
	}
}

void CameraStop::onDeveloperModeEnable()
{
	this->debugDraw->setVisible(true);
}

void CameraStop::onDeveloperModeDisable()
{
	this->debugDraw->setVisible(false);
}
