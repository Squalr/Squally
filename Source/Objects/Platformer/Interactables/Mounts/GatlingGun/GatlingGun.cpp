#include "GatlingGun.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Music.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Music/Tracks/FarAndAway.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_CAN_MOVE 1

const std::string GatlingGun::MapKey = "gatling-gun";

GatlingGun* GatlingGun::create(cocos2d::ValueMap& properties)
{
	GatlingGun* instance = new GatlingGun(properties);

	instance->autorelease();

	return instance;
}

GatlingGun::GatlingGun(cocos2d::ValueMap& properties) : super(properties, CSize(240.0f, 184.0f))
{
	ValueMap emptyProperties;
	this->parseDirection();
	this->mountSpeed = 0.0f;
	this->animations = SmartAnimationNode::create(""); // TODO
	this->body = Sprite::create(ObjectResources::Interactive_GatlingGun_GatlingGun);
	this->gauntletMusic = FarAndAway::create(emptyProperties);

	this->frontNode->addChild(this->animations);
	this->frontNode->addChild(this->body);
	this->addChild(this->gauntletMusic);
}

GatlingGun::~GatlingGun()
{
}

void GatlingGun::onEnter()
{
	super::onEnter();

	// Prime cache now to prevent lag spike later
	this->gauntletMusic->allocSound();

	this->scheduleUpdate();
}

void GatlingGun::initializePositions()
{
	super::initializePositions();
}

void GatlingGun::initializeListeners()
{
	super::initializeListeners();
	
	this->interactCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Entity }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});
}

void GatlingGun::update(float dt)
{
	super::update(dt);

	for (PlatformerEntity* mountedEntity : this->mountedEntities)
	{
		if (mountedEntity != nullptr)
		{
			mountedEntity->getAnimations()->setFlippedX(false);
		}
	}
}

void GatlingGun::playGauntletTrack()
{
	this->gauntletMusic->pushTrack();
}

void GatlingGun::stopGauntletTrack()
{
	this->gauntletMusic->popTrack();
}

void GatlingGun::mount(PlatformerEntity* interactingEntity)
{
	super::mount(interactingEntity);

	this->faceEntityTowardsDirection();
	this->isMoving = false;
}

void GatlingGun::dismount(PlatformerEntity* entity)
{
	super::dismount(entity);
	
	this->isMoving = false;
}

SmartAnimationNode* GatlingGun::getAnimations() const
{
	return this->animations;
}

Vec2 GatlingGun::getReparentPosition(PlatformerEntity* entity)
{
	return Vec2(-160.0f, 32.0f);
}
