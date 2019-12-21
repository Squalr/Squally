#include "EntityWeaponCollisionBehavior.h"

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
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityWeaponCollisionBehavior::MapKeyAttachedBehavior = "entity-weapon-collisions";
const Size EntityWeaponCollisionBehavior::DefaultWeaponSize = Size(64.0f, 128.0f);

EntityWeaponCollisionBehavior* EntityWeaponCollisionBehavior::create(GameObject* owner)
{
	EntityWeaponCollisionBehavior* instance = new EntityWeaponCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityWeaponCollisionBehavior::EntityWeaponCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->weaponSize = EntityWeaponCollisionBehavior::DefaultWeaponSize;
	this->weaponOffset = Vec2::ZERO;
	this->weaponCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->rebuildWeaponCollision();
	}
}

EntityWeaponCollisionBehavior::~EntityWeaponCollisionBehavior()
{
}

void EntityWeaponCollisionBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
	{
		this->rebuildWeaponCollision();
	}));
}

void EntityWeaponCollisionBehavior::enable()
{
	this->weaponCollision->setPhysicsEnabled(true);
}

void EntityWeaponCollisionBehavior::disable()
{
	this->weaponCollision->setPhysicsEnabled(false);
}

void EntityWeaponCollisionBehavior::setWeaponSize(Size weaponSize)
{
	this->weaponSize = weaponSize;
}

void EntityWeaponCollisionBehavior::setWeaponOffset(Vec2 weaponOffset)
{
	this->weaponOffset = weaponOffset;
}

void EntityWeaponCollisionBehavior::rebuildWeaponCollision()
{
	AnimationPart* mainhand = this->entity->getAnimations()->getAnimationPart("mainhand");

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
	
	if (this->weaponCollision != nullptr)
	{
		mainhand->removeTrackingObject(this->weaponCollision);
	}

	this->weaponCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->weaponSize, 1.0f, 8.0f, 0.0f),
		(int)weaponType,
		false,
		false
	);

	this->weaponCollision->setPosition(this->weaponOffset);
	this->weaponCollision->setPhysicsEnabled(false);
	mainhand->addTrackingObject(this->weaponCollision);
}
