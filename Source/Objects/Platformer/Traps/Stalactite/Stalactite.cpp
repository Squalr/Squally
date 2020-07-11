#include "Stalactite.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_APPLY_GRAVITY 1

const std::string Stalactite::MapKey = "stalactite";

Stalactite* Stalactite::create(ValueMap& properties)
{
	Stalactite* instance = new Stalactite(properties);
	
	instance->autorelease();

	return instance;
}

Stalactite::Stalactite(ValueMap& properties) : super(properties)
{
	this->sprite = Sprite::create(ObjectResources::Traps_Stalactite_Stalactite);
	this->collision = CollisionObject::create(CollisionObject::createBox(Size(40.0f, 112.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, true));
	this->isFalling = false;

	this->collision->addChild(this->sprite);
	this->addChild(this->collision);
}

Stalactite::~Stalactite()
{
}

void Stalactite::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Stalactite::initializePositions()
{
	super::initializePositions();
}

void Stalactite::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEventOnce(this->getListenEvent(), [=](ValueMap)
	{
		this->isFalling = true;
	});
}

void Stalactite::update(float dt)
{
	super::update(dt);

	this->applyGravity(dt);
}

void Stalactite::applyGravity(float dt)
{
	static const float Speed = -768.0f;

	if (!this->isFalling)
	{
		return;
	}

	this->setPositionY(this->getPositionY() + Speed * dt);
}
