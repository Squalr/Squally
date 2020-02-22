#include "CameraStop.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const std::string CameraStop::MapKeyCameraStop = "camera-stop";
const std::string CameraStop::MapKeyPropertySoft = "soft";
const std::string CameraStop::MapKeyPropertyNoX = "no-x";
const std::string CameraStop::MapKeyPropertyNoY = "no-y";

CameraStop* CameraStop::create(ValueMap& properties)
{
	CameraStop* instance = new CameraStop(properties);

	instance->autorelease();

	return instance;
}

CameraStop::CameraStop(ValueMap& properties) : super(properties)
{
	this->soft = GameUtils::getKeyOrDefault(this->properties, CameraStop::MapKeyPropertySoft, Value(false)).asBool();
	this->noX = GameUtils::getKeyOrDefault(this->properties, CameraStop::MapKeyPropertyNoX, Value(false)).asBool();
	this->noY = GameUtils::getKeyOrDefault(this->properties, CameraStop::MapKeyPropertyNoY, Value(false)).asBool();
	this->debugDraw = DrawNode::create();
	this->stopSize = Size(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(32.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(32.0f)).asFloat()
	);

	this->debugDraw->drawRect(-Vec2(this->stopSize / 2.0f), Vec2(this->stopSize / 2.0f), Color4F::GREEN);

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

	if (this->noX && this->noY)
	{
		return;
	}

	Vec2 thisCoords = GameUtils::getWorldCoords(this);
	Vec2 cameraCoords = GameCamera::getInstance()->getCameraPosition();
	Size cameraSize = Director::getInstance()->getVisibleSize() * GameCamera::getInstance()->getCameraZoom();

	Vec2 cameraDistance = thisCoords - cameraCoords;
	Vec2 cameraInset = cameraDistance + Vec2(cameraSize / 2.0f);
	
	// Determine how far into the screen each side is
	float leftSideInset = cameraSize.width / 2.0f - cameraDistance.x + this->stopSize.width / 2.0f;
	float rightSideInset = cameraSize.width - leftSideInset + this->stopSize.width;
	float bottomSideInset = cameraSize.height / 2.0f - cameraDistance.y + this->stopSize.height / 2.0f;
	float topSideInset = cameraSize.height - bottomSideInset + this->stopSize.height;

	if (std::abs(cameraDistance.x) <= cameraSize.width / 2.0f + this->stopSize.width / 2.0f &&
		std::abs(cameraDistance.y) <= cameraSize.height / 2.0f + this->stopSize.height / 2.0f)
	{
		Vec2 idealPosition = cameraCoords;

		if (!this->noX && leftSideInset <= rightSideInset && leftSideInset <= topSideInset && leftSideInset <= bottomSideInset)
		{
			idealPosition = Vec2(cameraCoords.x - leftSideInset, cameraCoords.y);
		}
		else if (!this->noX && rightSideInset <= topSideInset && rightSideInset <= bottomSideInset)
		{
			idealPosition = Vec2(cameraCoords.x + rightSideInset, cameraCoords.y);
		}
		else if (!this->noY && bottomSideInset <= topSideInset)
		{
			idealPosition = Vec2(cameraCoords.x, cameraCoords.y - bottomSideInset);
		}
		else if (!this->noY)
		{
			idealPosition = Vec2(cameraCoords.x, cameraCoords.y + topSideInset);
		}
		else
		{
			return;
		}

		if (this->soft)
		{
			const float SoftnessFactor = 256.0f;
			const float ScaleFactor = 1.6f;
			const Vec2 DistRatio = Vec2(
				MathUtils::clamp(std::abs(cameraDistance.x) / (cameraSize.width / 2.0f + this->stopSize.width / 2.0f), 0.0f, 1.0f),
				MathUtils::clamp(std::abs(cameraDistance.y) / (cameraSize.height / 2.0f + this->stopSize.height / 2.0f), 0.0f, 1.0f)
			);
			const Vec2 InvRatio = Vec2(1.0f - DistRatio.x, 1.0f - DistRatio.y);
			const Vec2 ScaledRatio = Vec2(
				MathUtils::clamp((1.0f - std::pow(InvRatio.x, ScaleFactor)), 0.0f, 1.0f),
				MathUtils::clamp((1.0f - std::pow(InvRatio.y, ScaleFactor)), 0.0f, 1.0f)
			);
			const Vec2 Softness = Vec2(1.0f + SoftnessFactor, 1.0f + SoftnessFactor) - SoftnessFactor * ScaledRatio;

			Vec2 offset = (cameraCoords - idealPosition);

			
			// Dampen the offset
			offset.x = offset.x * (ScaledRatio.x / Softness.x);
			offset.y = offset.y * (ScaledRatio.y / Softness.y);

			GameCamera::getInstance()->setCameraPosition(cameraCoords - offset);
		}
		else
		{
			GameCamera::getInstance()->setCameraPosition(idealPosition);
		}
	}
}

void CameraStop::onDeveloperModeEnable(int debugLevel)
{
	this->debugDraw->setVisible(true);
}

void CameraStop::onDeveloperModeDisable()
{
	this->debugDraw->setVisible(false);
}
