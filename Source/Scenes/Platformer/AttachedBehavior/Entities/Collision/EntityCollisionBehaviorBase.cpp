#include "EntityCollisionBehaviorBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityHeadCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const float EntityCollisionBehaviorBase::WaterJumpVelocity = 7680.0f;
const float EntityCollisionBehaviorBase::SwimVerticalDrag = 0.93f;
const float EntityCollisionBehaviorBase::StaticFriction = 256.0f;

EntityCollisionBehaviorBase::EntityCollisionBehaviorBase(GameObject* owner, int collisionType, int collisionTypeMovement) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->collisionType = collisionType | int(PlatformerCollisionType::Entity);
	this->collisionTypeMovement = collisionTypeMovement | int(PlatformerCollisionType::EntityMovement);
	this->entityCollision = nullptr;
	this->movementCollision = nullptr;
	this->groundCollision = nullptr;
	this->headCollision = nullptr;
	this->movementBehavior = nullptr;
	this->leftCollision = nullptr;
	this->rightCollision = nullptr;
	this->movementCollisionBound = false;
	this->submergeSound = WorldSound::create(SoundResources::Platformer_Environment_Splash1);
	this->emergeSound = WorldSound::create(SoundResources::Platformer_Environment_Emerge1);
	this->noEmergeSubmergeSoundCooldown = 1.0f;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->toggleQueryable(false);

	this->addChild(this->submergeSound);
	this->addChild(this->emergeSound);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->toggleQueryable(false);
}

EntityCollisionBehaviorBase::~EntityCollisionBehaviorBase()
{
}

void EntityCollisionBehaviorBase::onLoad()
{
	const std::string identifier = this->entity->getUniqueIdentifier();
	
	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventWarpToLocationPrefix + identifier, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::WarpObjectToLocationArgs* args = static_cast<PlatformerEvents::WarpObjectToLocationArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->warpToPosition(args->position, args->warpCamera);

			PlatformerEvents::TriggerAfterWarp(PlatformerEvents::AfterWarpArgs(this->entity));
		}
	}));

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventWarpToObjectIdPrefix + identifier, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::WarpObjectToObjectIdArgs* args = static_cast<PlatformerEvents::WarpObjectToObjectIdArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && !args->objectId.empty())
		{
			ObjectEvents::QueryObjects(QueryObjectsArgs<GameObject>([=](GameObject* object)
			{
				this->warpToPosition(GameUtils::getWorldCoords3D(object), args->warpCamera);
			}), args->objectId);

			PlatformerEvents::TriggerAfterWarp(PlatformerEvents::AfterWarpArgs(this->entity));
		}
	}));

	this->entity->watchForAttachedBehavior<EntityMovementBehavior>([=](EntityMovementBehavior* movementBehavior)
	{
		this->movementBehavior = movementBehavior;
	});

	this->entity->watchForAttachedBehavior<EntityGroundCollisionBehavior>([=](EntityGroundCollisionBehavior* groundCollision)
	{
		this->groundCollision = groundCollision;
	});

	this->entity->watchForAttachedBehavior<EntityHeadCollisionBehavior>([=](EntityHeadCollisionBehavior* headCollision)
	{
		this->headCollision = headCollision;
	});

	this->defer([=]()
	{
		this->buildWallDetectors();
		this->buildEntityCollision();
		this->buildMovementCollision();
		this->toggleQueryable(true);
		this->tryBind();
	});

	this->scheduleUpdate();
}

void EntityCollisionBehaviorBase::onDisable()
{
	super::onDisable();
	
	if (this->movementCollision != nullptr)
	{
		this->movementCollision->setPhysicsEnabled(false);
	}
}
void EntityCollisionBehaviorBase::update(float dt)
{
	super::update(dt);

	if (this->noEmergeSubmergeSoundCooldown > 0.0f)
	{
		this->noEmergeSubmergeSoundCooldown -= dt;
	}

	this->tryBind();
}

void EntityCollisionBehaviorBase::warpToPosition(Vec3 position, bool warpCamera)
{
	// Watch for own attached behavior -- this is to stall if this object is not queryable yet (and thus collision is not built yet)
	this->entity->watchForAttachedBehavior<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* behavior)
	{
		if (this->movementCollision != nullptr)
		{
			this->tryBind();
			this->movementCollision->warpTo(position);

			if (warpCamera && GameCamera::getInstance()->getCurrentTrackingData()->target == this->entity)
			{
				GameCamera::getInstance()->setCameraPositionToTrackedTarget();
			}
		}
	});
}

void EntityCollisionBehaviorBase::enableNormalPhysics()
{
	this->movementCollision->setGravityEnabled(true);
	this->movementCollision->setVerticalDampening(CollisionObject::DefaultVerticalDampening);
}

void EntityCollisionBehaviorBase::enableWaterPhysics()
{
	this->movementCollision->setGravityEnabled(false);
	this->movementCollision->setVerticalDampening(EntityCollisionBehaviorBase::SwimVerticalDrag);
}

Vec2 EntityCollisionBehaviorBase::getVelocity()
{
	return this->movementCollision == nullptr ? Vec2::ZERO : this->movementCollision->getVelocity();
}

void EntityCollisionBehaviorBase::setVelocity(Vec2 velocity)
{
	if (this->movementCollision == nullptr)
	{
		return;
	}

	this->movementCollision->setVelocity(velocity);
}

bool EntityCollisionBehaviorBase::hasLeftWallCollision()
{
	return this->leftCollision == nullptr ? false : !this->leftCollision->getCurrentCollisions().empty();
}

bool EntityCollisionBehaviorBase::hasRightWallCollision()
{
	return this->rightCollision == nullptr ? false : !this->rightCollision->getCurrentCollisions().empty();
}

bool EntityCollisionBehaviorBase::hasLeftWallCollisionWith(CollisionObject* collisonObject)
{
	for (auto next : this->leftCollision->getCurrentCollisions())
	{
		if (next == collisonObject)
		{
			return true;
		}
	}

	return false;
}

bool EntityCollisionBehaviorBase::hasRightWallCollisionWith(CollisionObject* collisonObject)
{
	for (auto next : this->rightCollision->getCurrentCollisions())
	{
		if (next == collisonObject)
		{
			return true;
		}
	}

	return false;
}

void EntityCollisionBehaviorBase::buildEntityCollision()
{
	if (this->entityCollision != nullptr || this->isInvalidated())
	{
		return;
	}

	const float ScaleFactor = 0.9f;

	this->entityCollision = CollisionObject::create(
		// CollisionObject::createBox(this->entity->getEntitySize() * ScaleFactor),
		CollisionObject::createCapsulePolygon(this->entity->getEntitySize() * ScaleFactor, 8.0f),
		(CollisionType)this->collisionType,
		CollisionObject::Properties(false, false),
		Color4F::TRANSPARENT_WHITE
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);

	this->entityCollision->setPosition(offset);
	this->entityCollision->setName("Entity collision");

	this->addChild(this->entityCollision);
	
	this->entityCollision->whileCollidesWith({ (int)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void EntityCollisionBehaviorBase::buildMovementCollision()
{
	if (this->movementCollision != nullptr || this->isInvalidated())
	{
		return;
	}

	this->movementCollision = CollisionObject::create(
		CollisionObject::createBox(this->entity->getEntitySize()),
		// CollisionObject::createCapsulePolygon(this->entity->getEntitySize(), 8.0f),
		(CollisionType)this->collisionTypeMovement,
		CollisionObject::Properties(true, false),
		Color4F::TRANSPARENT_WHITE
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);

	this->movementCollision->setPosition(offset);
	this->movementCollision->setName("Movement collision");

	this->addChild(this->movementCollision);

	this->movementCollision->whileCollidesWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
	
	this->movementCollision->whileCollidesWith({ (int)PlatformerCollisionType::SolidRoof }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->groundCollision == nullptr || this->headCollision == nullptr)
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		if (this->groundCollision->isStandingOn(collisionData.other))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		if (this->headCollision->hasHeadCollisionWith(collisionData.other))
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
	
	this->movementCollision->whileCollidesWith({ (int)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->groundCollision == nullptr || this->headCollision == nullptr)
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		// No collision when not standing on anything
		if (!this->groundCollision->isOnGround())
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		// No collision if we have both a ground and head collision with the pass-through (aka we are fully inside it)
		if (this->headCollision->hasHeadCollisionWith(collisionData.other))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		// No collision if we have both a ground and head collision with the pass-through (aka we are fully inside it)
		if (this->entityCollision->hasCollisionWith(collisionData.other))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		// This is how we allow platforms to overlap -- the oldest-touched platform tends to be the correct collision target
		if (!this->groundCollision->isStandingOnSomethingOtherThan(collisionData.other))
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		if (this->groundCollision->isStandingOn(collisionData.other))
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->groundCollision != nullptr
			&& !this->groundCollision->isOnGround()
			&& this->noEmergeSubmergeSoundCooldown <= 0.0f
			&& !this->submergeSound->isPlaying()
			&& !this->movementCollision->wasCollidingWithType((int)PlatformerCollisionType::Water))
		{
			this->submergeSound->play();
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->movementCollision->whileCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->entity->controlState = PlatformerEntity::ControlState::Swimming;

		// Clear current animation
		this->entity->getAnimations()->playAnimation();
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->movementCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->entity->controlState = PlatformerEntity::ControlState::Normal;

		if (this->groundCollision != nullptr
			&& !this->groundCollision->isOnGround()
			&& this->noEmergeSubmergeSoundCooldown <= 0.0f
			&& !this->emergeSound->isPlaying()
			&& !this->movementCollision->isCollidingWithType((int)PlatformerCollisionType::Water))
		{
			this->emergeSound->play();
		}

		if (this->movementBehavior != nullptr)
		{
			this->movementBehavior->cancelWaterSfx();
		}

		// Animate jumping out of water
		if (this->movementCollision->getVelocity().y > 0.0f && this->entity->getRuntimeStateOrDefaultFloat(StateKeys::MovementY, 0.0f) > 0.0f)
		{
			// Give a velocity boost for jumping out of water
			this->movementCollision->setVelocity(Vec2(this->movementCollision->getVelocity().x, EntityCollisionBehaviorBase::WaterJumpVelocity));

			this->entity->getAnimations()->playAnimation(this->entity->getJumpAnimation(), SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(0.85f));
		}
		else
		{
			if (this->entity->getAnimations()->getCurrentAnimation() == this->entity->getSwimAnimation())
			{
				this->entity->getAnimations()->clearAnimationPriority();
			}

			this->entity->getAnimations()->playAnimation();
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->onEntityCollisionCreated();
}

void EntityCollisionBehaviorBase::buildWallDetectors()
{
	if (this->leftCollision != nullptr || this->rightCollision != nullptr || this->isInvalidated())
	{
		return;
	}

	const Size wallDetectorSize = Size(std::max(this->entity->getEntitySize().width / 2.0f - 8.0f, 16.0f), std::max(this->entity->getEntitySize().height - 32.0f, 16.0f));

	this->leftCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(wallDetectorSize, 8.0f),
		(int)PlatformerCollisionType::WallDetector,
		CollisionObject::Properties(false, false)
	);
	this->rightCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(wallDetectorSize, 8.0f),
		(int)PlatformerCollisionType::WallDetector,
		CollisionObject::Properties(false, false)
	);

	this->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Size entitySize = this->entity->getEntitySize();

	// Padding
	entitySize.width += 8.0f;

	Vec2 offsetLeft = collisionOffset + Vec2(-entitySize.width / 2.0f + wallDetectorSize.width / 2.0f, entitySize.height / 2.0f + this->entity->getHoverHeight() / 2.0f);
	Vec2 offsetRight = collisionOffset + Vec2(entitySize.width / 2.0f - wallDetectorSize.width / 2.0f, entitySize.height / 2.0f + this->entity->getHoverHeight() / 2.0f);

	this->leftCollision->setPosition(offsetLeft);
	this->rightCollision->setPosition(offsetRight);

	this->addChild(this->leftCollision);
	this->addChild(this->rightCollision);
}

void EntityCollisionBehaviorBase::tryBind()
{
	if (this->movementCollision != nullptr && !this->movementCollisionBound)
	{
		this->movementCollisionBound = true;
		this->movementCollision->bindTo(this->entity);
	}
}
