#include "FlyBotMovementBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/Helpers/EndianForest/FlyBot.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string FlyBotMovementBehavior::MapKeyAttachedBehavior = "flybot-movement";
const float FlyBotMovementBehavior::FloatOffsetRadius = 256.0f;
const float FlyBotMovementBehavior::FloatOffsetAngle = 60.0f * float(M_PI) / 180.0f;
const Vec2 FlyBotMovementBehavior::FlySpeedBase = Vec2(128.0f, 128.0f);
const float FlyBotMovementBehavior::FlySpeedDistanceMultiplier = 1.05f;

FlyBotMovementBehavior* FlyBotMovementBehavior::create(GameObject* owner)
{
	FlyBotMovementBehavior* instance = new FlyBotMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

FlyBotMovementBehavior::FlyBotMovementBehavior(GameObject* owner) : super(owner)
{
	this->flyBot = dynamic_cast<FlyBot*>(owner);
	this->elapsed = 0.0f;

	if (this->flyBot == nullptr)
	{
		this->invalidate();
	}

	this->squally = nullptr;
}

FlyBotMovementBehavior::~FlyBotMovementBehavior()
{
}

void FlyBotMovementBehavior::onLoad()
{
	this->scheduleUpdate();
}

void FlyBotMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr)
	{
		ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([&](Squally* squally)
		{
			this->squally = squally;
		}));

		return;
	}

	this->elapsed += dt;

	Vec2 destPosition = this->squally->getPosition();

	if (this->squally->getAnimations()->getFlippedX())
	{
		destPosition += Vec2(
			std::cos(FlyBotMovementBehavior::FloatOffsetAngle) * FlyBotMovementBehavior::FloatOffsetRadius,
			std::sin(FlyBotMovementBehavior::FloatOffsetAngle) * FlyBotMovementBehavior::FloatOffsetRadius
		);
	}
	else
	{
		destPosition += Vec2(
			std::cos(float(M_PI) - FlyBotMovementBehavior::FloatOffsetAngle) * FlyBotMovementBehavior::FloatOffsetRadius,
			std::sin(float(M_PI) - FlyBotMovementBehavior::FloatOffsetAngle) * FlyBotMovementBehavior::FloatOffsetRadius
		);
	}

	float distance = destPosition.distance(this->flyBot->getPosition());
	bool isLeftOfSqually = this->flyBot->getPositionX() <= this->squally->getPositionX();
	bool isMovingLeft = this->flyBot->getPositionX() > destPosition.x;
	bool isNearDest = distance < 8.0f;
	bool flipX = false;

	if (isNearDest)
	{
		flipX = this->squally->getAnimations()->getFlippedX();
	}
	else if (isMovingLeft)
	{
		flipX = true;
	}

	this->flyBot->getAnimations()->setFlippedX(flipX);
	this->flyBot->getFloatNode()->setPositionY(sin(2.25f * this->elapsed) * 24.0f);

	if (isNearDest)
	{
		return;
	}

	float angleBetween = -std::atan2(this->flyBot->getPositionY() - destPosition.y, this->flyBot->getPositionX() - destPosition.x);
	float speedBonus = distance * FlyBotMovementBehavior::FlySpeedDistanceMultiplier;
	
	Vec2 speed = Vec2(
		(FlyBotMovementBehavior::FlySpeedBase.x + speedBonus) * -std::cos(angleBetween),
		(FlyBotMovementBehavior::FlySpeedBase.y + speedBonus) * std::sin(angleBetween)
	);

	this->flyBot->setPosition(this->flyBot->getPosition() + speed * dt);
}
