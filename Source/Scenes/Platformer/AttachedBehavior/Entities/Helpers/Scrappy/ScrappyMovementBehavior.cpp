#include "ScrappyMovementBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string ScrappyMovementBehavior::MapKeyAttachedBehavior = "scrappy-movement";
const float ScrappyMovementBehavior::FloatOffsetRadius = 256.0f;
const float ScrappyMovementBehavior::FloatOffsetAngle = 60.0f * float(M_PI) / 180.0f;
const Vec2 ScrappyMovementBehavior::FlySpeedBase = Vec2(256.0f, 256.0f);
const float ScrappyMovementBehavior::FlySpeedDistanceMultiplier = 1.01f;

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
	this->timeNearDestX = 0.0f;
	this->timeNearDestY = 0.0f;

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
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	this->scheduleUpdate();
}

void ScrappyMovementBehavior::update(float dt)
{
	super::update(dt);

	const float NearDestTimeout = 0.75f;
	const float NearDistanceCheck = 8.0f;

	this->elapsed += dt;

	if (this->squally == nullptr)
	{
		return;
	}

	Vec2 squallyPosition = GameUtils::getWorldCoords(this->squally);
	Vec2 destPosition = squallyPosition;

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

	bool isLeftOfSqually = this->scrappy->getPositionX() <= squallyPosition.x;
	bool isMovingLeft = this->scrappy->getPositionX() > destPosition.x;
	bool isMovingUp = this->scrappy->getPositionY() > destPosition.y;
	bool isNearDestX = std::abs(destPosition.x - this->scrappy->getPositionX()) <= NearDistanceCheck;
	bool isNearDestY = std::abs(destPosition.y - this->scrappy->getPositionY()) <= NearDistanceCheck;
	bool flipX = false;

	if (isNearDestX)
	{
		this->timeNearDestX += dt;
		flipX = this->squally->getAnimations()->getFlippedX();
	}
	else
	{
		this->timeNearDestX = 0.0f;

		if (isMovingLeft)
		{
			flipX = true;
		}
	}

	if (isNearDestY)
	{
		this->timeNearDestY += dt;
	}
	else
	{
		this->timeNearDestY = 0.0f;
	}

	this->scrappy->getAnimations()->setFlippedX(flipX);
	this->scrappy->getFloatNode()->setPositionY(sin(2.25f * this->elapsed) * 24.0f);

	float distance = destPosition.distance(this->scrappy->getPosition());
	float squallyDistance = this->scrappy->getPosition().distance(squallyPosition);
	float angleBetween = -std::atan2(this->scrappy->getPositionY() - destPosition.y, this->scrappy->getPositionX() - destPosition.x);
	float speedBonus = MathUtils::clamp(squallyDistance - ScrappyMovementBehavior::FloatOffsetRadius, 0.0f, 1024.0f);
	
	Vec2 speed = Vec2(
		(ScrappyMovementBehavior::FlySpeedBase.x + speedBonus) * -std::cos(angleBetween),
		(ScrappyMovementBehavior::FlySpeedBase.y + speedBonus) * std::sin(angleBetween)
	);

	if (this->timeNearDestX < NearDestTimeout)
	{
		this->scrappy->setPositionX(this->scrappy->getPositionX() + speed.x * dt);

		// Overshot X -- time out instantly
		if ((isMovingLeft && this->scrappy->getPositionX() < destPosition.x) ||
			(!isMovingLeft && this->scrappy->getPositionX() > destPosition.x))
		{
			this->timeNearDestX = NearDestTimeout;
		}
	}

	if (this->timeNearDestY < NearDestTimeout)
	{
		this->scrappy->setPositionY(this->scrappy->getPositionY() + speed.y * dt);

		// Overshot Y -- time out instantly
		if ((isMovingUp && this->scrappy->getPositionY() < destPosition.y) ||
			(!isMovingUp && this->scrappy->getPositionY() > destPosition.y))
		{
			this->timeNearDestY = NearDestTimeout;
		}
	}
}
