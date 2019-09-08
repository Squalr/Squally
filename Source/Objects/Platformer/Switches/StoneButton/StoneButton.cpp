#include "StoneButton.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string StoneButton::MapKeyStoneButton = "stone-button";
const float StoneButton::ButtonPressureSpeed = 32.0f;
const float StoneButton::ButtonPressureOffsetMin = 8.0f;

StoneButton* StoneButton::create(ValueMap& properties)
{
	StoneButton* instance = new StoneButton(properties);

	instance->autorelease();

	return instance;
}

StoneButton::StoneButton(ValueMap& properties) : super(properties)
{
	this->button = Sprite::create(ObjectResources::Switches_StoneButton_StoneButtonTop);
	this->buttonBase = Sprite::create(ObjectResources::Switches_StoneButton_StoneButtonBase);
	this->buttonCollision = CollisionObject::create(PhysicsBody::createBox(Size(224.0f, 48.0f)), (CollisionType)PlatformerCollisionType::Solid, false, false);

	this->maxDefaultButtonPosition = 48.0f;

	this->buttonCollision->addChild(this->button);
	this->addChild(this->buttonCollision);
	this->addChild(this->buttonBase);
}

StoneButton::~StoneButton()
{
}

void StoneButton::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void StoneButton::initializePositions()
{
	super::initializePositions();

	this->buttonCollision->setPosition(Vec2(0.0f, this->maxDefaultButtonPosition));
}

void StoneButton::initializeListeners()
{
	super::initializeListeners();

	this->buttonCollision->whenCollidesWith({(int)PlatformerCollisionType::Force, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics}, [=](CollisionObject::CollisionData data)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

void StoneButton::update(float dt)
{
	super::update(dt);

	float currentPositionY = this->buttonCollision->getPositionY();

	if (this->buttonCollision->getCurrentCollisions().empty())
	{
		currentPositionY += StoneButton::ButtonPressureSpeed * dt;
	}
	else
	{
		currentPositionY -= StoneButton::ButtonPressureSpeed * dt;
	}

	currentPositionY = MathUtils::clamp(currentPositionY, StoneButton::ButtonPressureOffsetMin, this->maxDefaultButtonPosition);

	if (currentPositionY != this->buttonCollision->getPositionY())
	{
		this->buttonCollision->setPosition(Vec2(0.0f, currentPositionY));

		float progress = MathUtils::clamp(
			(this->maxDefaultButtonPosition - currentPositionY) / (this->maxDefaultButtonPosition - StoneButton::ButtonPressureOffsetMin),
			0.0f, 1.0f
		);
		ValueMap args = {
			{ SwitchEvents::SwitchArgProgress, Value(progress) },
		};

		ObjectEvents::TriggerBroadCastMapObjectState(this->sendEvent, args);
	}
}

Vec2 StoneButton::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void StoneButton::registerHackables()
{
	super::registerHackables();
}
