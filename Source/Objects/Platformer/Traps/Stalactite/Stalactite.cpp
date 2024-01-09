#include "Stalactite.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
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
	this->collision = CollisionObject::create(CollisionObject::createBox(CSize(40.0f, 112.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, true));
	this->rumbleSound = WorldSound::create(SoundResources::Platformer_Objects_Stalactite_RockFall1);
	this->fallSound = WorldSound::create(SoundResources::Platformer_Objects_Stalactite_RockFall2);

	this->collision->setCascadeOpacityEnabled(true);
	this->collision->addChild(this->sprite);

	this->collision->addChild(this->sprite);
	this->collision->addChild(this->rumbleSound);
	this->collision->addChild(this->fallSound);
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
		const float RotationAngle = 2.5f;
		const float RotationSpeed = 0.05f;
		const float HalfRotationSpeed = RotationSpeed / 2.0f;
		const float RumbleTime = 1.0f;
		const int Rumbles = int(std::round((RumbleTime - RotationSpeed) / RotationSpeed)) / 2;

		this->rumbleSound->play();
		
		this->runAction(Sequence::create(
			EaseSineInOut::create(RotateTo::create(HalfRotationSpeed, RotationAngle)),
			Repeat::create(Sequence::create(
				EaseSineInOut::create(RotateTo::create(RotationSpeed, -RotationAngle)),
				EaseSineInOut::create(RotateTo::create(RotationSpeed, RotationAngle)),
				nullptr
			), Rumbles),
			EaseSineInOut::create(RotateTo::create(HalfRotationSpeed, 0.0f)),
			CallFunc::create([=]()
			{
				this->isFalling = true;
				this->fallSound->play();
			}),
			nullptr
		));
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
