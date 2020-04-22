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

const std::string ScrappyMovementBehavior::MapKey = "scrappy-movement";
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
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	this->scheduleUpdate();
}

void ScrappyMovementBehavior::onDisable()
{
	super::onDisable();
}

void ScrappyMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->scrappy == nullptr || this->squally == nullptr)
	{
		return;
	}

	this->scrappy->getFloatNode()->setPositionY(sin(2.25f * this->elapsed) * 24.0f);
	
	const float NearDistanceCheck = 8.0f;

	this->elapsed += dt;

	Vec3 scrappyPosition = GameUtils::getWorldCoords3D(this->scrappy);
	Vec3 squallyPosition = GameUtils::getWorldCoords3D(this->squally);
	Vec3 parentDelta = this->scrappy->getPosition3D() - scrappyPosition;
	Vec3 destPosition = squallyPosition;

	if (this->squally->isFlippedX())
	{
		destPosition.x += std::cos(ScrappyMovementBehavior::FloatOffsetAngle) * ScrappyMovementBehavior::FloatOffsetRadius;
		destPosition.y += std::sin(ScrappyMovementBehavior::FloatOffsetAngle) * ScrappyMovementBehavior::FloatOffsetRadius;
	}
	else
	{
		destPosition.x += std::cos(float(M_PI) - ScrappyMovementBehavior::FloatOffsetAngle) * ScrappyMovementBehavior::FloatOffsetRadius;
		destPosition.y += std::sin(float(M_PI) - ScrappyMovementBehavior::FloatOffsetAngle) * ScrappyMovementBehavior::FloatOffsetRadius;
	}

	bool isLeftOfSqually = scrappyPosition.x <= squallyPosition.x;
	bool isDestinationLeft = scrappyPosition.x > destPosition.x;
	bool isDestinationUp = scrappyPosition.y > destPosition.y;
	bool isNearDestX = std::abs(destPosition.x - scrappyPosition.x) <= NearDistanceCheck;
	bool isNearDestY = std::abs(destPosition.y - scrappyPosition.y) <= NearDistanceCheck;
	bool flipX = false;

	if (isNearDestX)
	{
		flipX = this->squally->isFlippedX();
	}
	else
	{
		if (isDestinationLeft)
		{
			flipX = true;
		}
	}

	this->scrappy->getAnimations()->setFlippedX(flipX);

	if (isNearDestX && isNearDestY)
	{
		return;
	}

	float distance = destPosition.distance(scrappyPosition);
	float squallyDistance = scrappyPosition.distance(squallyPosition);
	float angleBetween = -std::atan2(scrappyPosition.y - destPosition.y, scrappyPosition.x - destPosition.x);

	// Bonus speed for Scrappy the further they are away from Squally
	float speedBonus = MathUtils::clamp(squallyDistance - ScrappyMovementBehavior::FloatOffsetRadius, 0.0f, 1024.0f);
	
	Vec2 speed = Vec2(
		(ScrappyMovementBehavior::FlySpeedBase.x + speedBonus) * -std::cos(angleBetween),
		(ScrappyMovementBehavior::FlySpeedBase.y + speedBonus) * std::sin(angleBetween)
	);

	this->scrappy->setPositionX(scrappyPosition.x + parentDelta.x + speed.x * dt);
	this->scrappy->setPositionY(scrappyPosition.y + parentDelta.y + speed.y * dt);
	this->scrappy->setPositionZ(squallyPosition.z + parentDelta.z);
}
