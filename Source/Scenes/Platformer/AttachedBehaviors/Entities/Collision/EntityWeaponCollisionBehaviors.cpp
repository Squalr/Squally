#include "EntityWeaponCollisionBehaviors.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityWeaponCollisionBehaviors::MapKeyAttachedBehavior = "entity-weapon-collisions";
const Size EntityWeaponCollisionBehaviors::DefaultWeaponSize = Size(64.0f, 128.0f);

EntityWeaponCollisionBehaviors* EntityWeaponCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityWeaponCollisionBehaviors* instance = new EntityWeaponCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityWeaponCollisionBehaviors::EntityWeaponCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->weaponSize = EntityWeaponCollisionBehaviors::DefaultWeaponSize;
	this->weaponOffset = Vec2::ZERO;
}

EntityWeaponCollisionBehaviors::~EntityWeaponCollisionBehaviors()
{
}

void EntityWeaponCollisionBehaviors::onLoad()
{
	this->rebuildWeaponCollision();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
	{
		this->rebuildWeaponCollision();
	}));
}

void EntityWeaponCollisionBehaviors::enable()
{
	this->weaponCollision->setPhysicsEnabled(true);
}

void EntityWeaponCollisionBehaviors::disable()
{
	this->weaponCollision->setPhysicsEnabled(false);
}

void EntityWeaponCollisionBehaviors::setWeaponSize(Size weaponSize)
{
	this->weaponSize = weaponSize;
}

void EntityWeaponCollisionBehaviors::setWeaponOffset(Vec2 weaponOffset)
{
	this->weaponOffset = weaponOffset;
}

void EntityWeaponCollisionBehaviors::rebuildWeaponCollision()
{
	AnimationPart* mainhand = this->entity->animationNode->getAnimationPart("mainhand");

	if (mainhand == nullptr)
	{
		return;
	}

	PlatformerCollisionType weaponType = PlatformerCollisionType::EnemyWeapon;
	Squally* squally = dynamic_cast<Squally*>(this->entity);
	PlatformerFriendly* npc = dynamic_cast<PlatformerFriendly*>(this->entity);

	if (squally != nullptr)
	{
		weaponType = PlatformerCollisionType::PlayerWeapon;
	}
	else if (npc != nullptr)
	{
		weaponType = PlatformerCollisionType::NpcWeapon;
	}
	
	mainhand->removeTrackingObject(this->weaponCollision);

	this->weaponCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->weaponSize, 1.0f, 8.0f),
		(int)weaponType,
		false,
		false
	);

	this->weaponCollision->setPosition(this->weaponOffset);
	this->weaponCollision->setPhysicsEnabled(false);
	mainhand->addTrackingObject(this->weaponCollision);
}
