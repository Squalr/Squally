#include "ScrappyMovementBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string ScrappyMovementBehavior::MapKeyAttachedBehavior = "Scrappy-movement";
const float ScrappyMovementBehavior::FloatOffsetRadius = 256.0f;
const float ScrappyMovementBehavior::FloatOffsetAngle = 60.0f * float(M_PI) / 180.0f;
const Vec2 ScrappyMovementBehavior::FlySpeedBase = Vec2(128.0f, 128.0f);
const float ScrappyMovementBehavior::FlySpeedDistanceMultiplier = 1.05f;

ScrappyMovementBehavior* ScrappyMovementBehavior::create(GameObject* owner)
{
	ScrappyMovementBehavior* instance = new ScrappyMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

ScrappyMovementBehavior::ScrappyMovementBehavior(GameObject* owner) : super(owner)
{
	this->scrappy = dynamic_cast<Scrappy*>(owner);
	this->elapsed = 0.0f;
	this->timeNearDest = 0.0f;

	if (this->scrappy == nullptr)
	{
		this->invalidate();
	}

	this->squally = nullptr;
}

ScrappyMovementBehavior::~ScrappyMovementBehavior()
{
}

void ScrappyMovementBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, &this->squally);

	this->scheduleUpdate();
}

void ScrappyMovementBehavior::update(float dt)
{
	super::update(dt);

	this->elapsed += dt;

	if (this->squally == nullptr)
	{
		return;
	}

	Vec2 destPosition = this->squally->getPosition();

	if (this->squally->getAnimations()->getFlippedX())
	{
		destPosition += Vec2(
			std::cos(ScrappyMovementBehavior::FloatOffsetAngle) * ScrappyMovementBehavior::FloatOffsetRadius,
			std::sin(ScrappyMovementBehavior::FloatOffsetAngle) * ScrappyMovementBehavior::FloatOffsetRadius
		);
	}
	else
	{
		destPosition += Vec2(
			std::cos(float(M_PI) - ScrappyMovementBehavior::FloatOffsetAngle) * ScrappyMovementBehavior::FloatOffsetRadius,
			std::sin(float(M_PI) - ScrappyMovementBehavior::FloatOffsetAngle) * ScrappyMovementBehavior::FloatOffsetRadius
		);
	}

	float distance = destPosition.distance(this->scrappy->getPosition());
	bool isLeftOfSqually = this->scrappy->getPositionX() <= this->squally->getPositionX();
	bool isMovingLeft = this->scrappy->getPositionX() > destPosition.x;
	bool isNearDest = distance < 8.0f;
	bool flipX = false;

	if (isNearDest)
	{
		this->timeNearDest += dt;
	}
	else
	{
		this->timeNearDest = 0.0f;
	}

	if (isNearDest)
	{
		flipX = this->squally->getAnimations()->getFlippedX();
	}
	else if (isMovingLeft)
	{
		flipX = true;
	}

	this->scrappy->getAnimations()->setFlippedX(flipX);
	this->scrappy->getFloatNode()->setPositionY(sin(2.25f * this->elapsed) * 24.0f);

	if (isNearDest && this->timeNearDest > 0.75f)
	{
		return;
	}

	float angleBetween = -std::atan2(this->scrappy->getPositionY() - destPosition.y, this->scrappy->getPositionX() - destPosition.x);
	float speedBonus = distance * ScrappyMovementBehavior::FlySpeedDistanceMultiplier;
	
	Vec2 speed = Vec2(
		(ScrappyMovementBehavior::FlySpeedBase.x + speedBonus) * -std::cos(angleBetween),
		(ScrappyMovementBehavior::FlySpeedBase.y + speedBonus) * std::sin(angleBetween)
	);

	this->scrappy->setPosition(this->scrappy->getPosition() + speed * dt);
}
