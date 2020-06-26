#include "StoneButton.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string StoneButton::MapKey = "stone-button";
const std::string StoneButton::PropertySwitch = "switch";
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
	this->buttonCollision = CollisionObject::create(CollisionObject::createBox(Size(224.0f, 48.0f)), (CollisionType)PlatformerCollisionType::Solid, CollisionObject::Properties(false, false));
	this->isSwitch = GameUtils::getKeyOrDefault(this->properties, StoneButton::PropertySwitch, Value(false)).asBool();
	this->buttonSound = WorldSound::create(SoundResources::Platformer_Objects_Machines_RollLoop1);
	this->maxDefaultButtonPosition = 48.0f;
	this->hasCollided = false;

	this->buttonCollision->addChild(this->button);
	this->addChild(this->buttonCollision);
	this->addChild(this->buttonBase);
	this->addChild(this->buttonSound);
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

	this->buttonCollision->whenCollidesWith({ (int)PlatformerCollisionType::Force, (int)PlatformerCollisionType::Entity, (int)PlatformerCollisionType::Hover, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData data)
	{
		this->hasCollided = true;
		
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

void StoneButton::update(float dt)
{
	super::update(dt);

	float currentPositionY = this->buttonCollision->getPositionY();

	if (!this->buttonCollision->getCurrentCollisions().empty() || (this->isSwitch && this->hasCollided))
	{
		currentPositionY -= StoneButton::ButtonPressureSpeed * dt;
	}
	else
	{
		currentPositionY += StoneButton::ButtonPressureSpeed * dt;
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

		if (!this->buttonSound->isPlaying())
		{
			this->buttonSound->play();
		}

		this->broadcastMapEvent(this->getSendEvent(), args);
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
