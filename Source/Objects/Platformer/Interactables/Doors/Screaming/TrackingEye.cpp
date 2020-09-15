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
	this->squally = nullptr;

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

	this->updateEyeTracking();
}

void TrackingEye::updateEyeTracking()
{
	if (this->squally == nullptr)
	{
		return;
	}
	
	static const Size HalfScreenSize = Director::getInstance()->getVisibleSize() / 2.0f;

	Vec2 thisCoords = GameUtils::getWorldCoords(this, false);
	Vec2 squallyCoords = GameUtils::getWorldCoords(this->squally, false);

	Vec2 progress = Vec2(
		MathUtils::clamp((squallyCoords.x - thisCoords.x) / HalfScreenSize.width, -1.0f, 1.0f),
		MathUtils::clamp((squallyCoords.y - thisCoords.y) / HalfScreenSize.height, -1.0f, 1.0f)
	);
	
	Vec2 unit = Vec2(
		MathUtils::clamp((squallyCoords.x - thisCoords.x) / HalfScreenSize.width, -1.0f, 1.0f),
		MathUtils::clamp((squallyCoords.y - thisCoords.y) / HalfScreenSize.height, -1.0f, 1.0f)
	);

	unit.normalize();

	progress = unit; // Vec2(std::min(progress.x, unit.x), std::min(progress.y, unit.y));

	Vec2 accumulator = Vec2::ZERO;

	for (int index = 0; index < int(this->eyeParts.size()); index++)
	{
		accumulator += Vec2(
			progress.x * this->leeway[index],
			progress.y * this->leeway[index]
		);

		this->eyeParts[index]->setPosition(accumulator);
	}
}
