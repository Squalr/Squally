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

CameraStop::CameraStop(ValueMap& properties) : super(properties)
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
	Vec2 cameraInset = cameraDistance + Vec2(visibleSize / 2.0f);
	
	// Determine how far into the screen each side is
	float leftSideInset = visibleSize.width / 2.0f - cameraDistance.x + this->stopSize.width / 2.0f;
	float rightSideInset = visibleSize.width - leftSideInset + this->stopSize.width;
	float topSideInset = visibleSize.height / 2.0f - cameraDistance.y + this->stopSize.height / 2.0f;
	float bottomSideInset = topSideInset + visibleSize.height + this->stopSize.height;

	if (std::abs(cameraDistance.x) <= visibleSize.width / 2.0f + this->stopSize.width / 2.0f &&
		std::abs(cameraDistance.y) <= visibleSize.height / 2.0f + this->stopSize.height / 2.0f)
	{
		if (leftSideInset <= rightSideInset && leftSideInset <= topSideInset && leftSideInset <= bottomSideInset)
		{
			GameCamera::getInstance()->setCameraPosition(Vec2(cameraCoords.x - leftSideInset, cameraCoords.y));
		}
		else if (rightSideInset <= topSideInset && rightSideInset <= bottomSideInset)
		{
			GameCamera::getInstance()->setCameraPosition(Vec2(cameraCoords.x + rightSideInset, cameraCoords.y));
		}
		else if (topSideInset <= bottomSideInset)
		{
			GameCamera::getInstance()->setCameraPosition(Vec2(cameraCoords.x, cameraCoords.y - topSideInset));
		}
		else
		{
			GameCamera::getInstance()->setCameraPosition(Vec2(cameraCoords.x, cameraCoords.y  + bottomSideInset));
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
