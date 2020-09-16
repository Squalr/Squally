#include "TrackingEye.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string TrackingEye::MapKey = "tracking-eye";

TrackingEye* TrackingEye::create()
{
	TrackingEye* instance = new TrackingEye();

	instance->autorelease();

	return instance;
}

TrackingEye::TrackingEye() : super()
{
	this->eyeBase = Sprite::create(ObjectResources::Doors_ScreamingDoor_EyeBase);
	this->eyeInner = Sprite::create(ObjectResources::Doors_ScreamingDoor_EyeInner);
	this->eyeRing = Sprite::create(ObjectResources::Doors_ScreamingDoor_EyeRing);
	this->eyePupil = Sprite::create(ObjectResources::Doors_ScreamingDoor_EyePupil);
	this->eyeParts = std::vector<cocos2d::Sprite*>();
	this->leeway = std::vector<float>();
	this->pairedEye = nullptr;
	this->squally = nullptr;
	this->eyeVector = Vec2::ZERO;

	this->eyeParts.push_back(this->eyeBase);
	this->eyeParts.push_back(this->eyeInner);
	this->eyeParts.push_back(this->eyeRing);
	this->eyeParts.push_back(this->eyePupil);

	this->leeway.push_back(11.0f);
	this->leeway.push_back(5.0f - 2.0f);
	this->leeway.push_back(8.0f);
	this->leeway.push_back(10.0f - 3.0f);

	this->addChild(this->eyeBase);
	this->addChild(this->eyeInner);
	this->addChild(this->eyeRing);
	this->addChild(this->eyePupil);
}

TrackingEye::~TrackingEye()
{
}

void TrackingEye::onEnter()
{
	super::onEnter();

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	this->scheduleUpdate();
}

void TrackingEye::initializePositions()
{
	super::initializePositions();
}

void TrackingEye::update(float dt)
{
	super::update(dt);

	this->updateEyeTracking(dt);
}

void TrackingEye::pair(TrackingEye* pairedEye)
{
	this->pairedEye = pairedEye;
}

void TrackingEye::updateEyeTracking(float dt)
{
	if (this->squally == nullptr)
	{
		return;
	}

	/*
		THIS CODE WORKS AS FOLLOWS:
		Case 1:
			The player is between the eyes. Each eye will then be processed individually, looking at the player according to the unit vector in the direction of the player.

		Case 2:
			The player is outside the eyes. The eye furthest from the player will be used to calculate the direction of both eyes, to keep them in sync.
			Either the unit vector OR a distance-ratio vector is used, whichever is smallest. Unit vector only allows for the pupil to be placed on the edge of the eye,
			but a distance-ratio vector allows for the pupil to be between the center and the edge of the eye.

		In both cases, gradual blending is used to prevent "snapping" motions

	*/
	
	static const Size HalfScreenSize = Director::getInstance()->getVisibleSize() / 2.0f;
	static const float EyeSpeed = 8.0f;

	Vec2 thisCoords = GameUtils::getWorldCoords(this, false);
	Vec2 pairedCoords = this->pairedEye == nullptr ? thisCoords : GameUtils::getWorldCoords(this->pairedEye, false);
	Vec2 squallyCoords = GameUtils::getWorldCoords(this->squally, false);
	Vec2 furthestEyeCoords = thisCoords.distance(squallyCoords) >= pairedCoords.distance(squallyCoords) ? thisCoords : pairedCoords;
	bool isBetweenEyes = (thisCoords.x >= squallyCoords.x && pairedCoords.x <= squallyCoords.x) || (pairedCoords.x >= squallyCoords.x && thisCoords.x <= squallyCoords.x);
	Vec2 activeEyeCoords = isBetweenEyes ? thisCoords : furthestEyeCoords;

	Vec2 distanceRatio = Vec2(
		MathUtils::clamp((squallyCoords.x - activeEyeCoords.x) / HalfScreenSize.width, -1.0f, 1.0f),
		MathUtils::clamp((squallyCoords.y - activeEyeCoords.y) / HalfScreenSize.height, -1.0f, 1.0f)
	);
	
	Vec2 unit = distanceRatio;
	Vec2 sign = Vec2(unit.x < 0.0f ? -1.0f : 1.0f, unit.y < 0.0f ? -1.0f : 1.0f);

	unit.normalize();

	Vec2 eyeVectorIdeal = isBetweenEyes ? unit : Vec2(sign.x * std::min(std::abs(distanceRatio.x), std::abs(unit.x)), sign.y * std::min(std::abs(distanceRatio.y), std::abs(unit.y)));

	// Gradually move towards ideal position to prevent snapping movements
	this->eyeVector = this->eyeVector + (eyeVectorIdeal - this->eyeVector) * (dt * EyeSpeed);

	Vec2 accumulator = Vec2::ZERO;

	for (int index = 0; index < int(this->eyeParts.size()); index++)
	{
		accumulator += Vec2(
			this->eyeVector.x * this->leeway[index],
			this->eyeVector.y * this->leeway[index]
		);

		this->eyeParts[index]->setPosition(accumulator);
	}
}
