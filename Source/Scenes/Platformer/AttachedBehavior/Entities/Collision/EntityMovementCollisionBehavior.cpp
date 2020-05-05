#include "EntityMovementCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
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

const std::string EntityMovementCollisionBehavior::MapKey = "entity-movement-collisions";
const float EntityMovementCollisionBehavior::WaterJumpVelocity = 7680.0f;
const float EntityMovementCollisionBehavior::SwimVerticalDrag = 0.93f;
const float EntityMovementCollisionBehavior::StaticFriction = 256.0f;

EntityMovementCollisionBehavior* EntityMovementCollisionBehavior::create(GameObject* owner)
{
	EntityMovementCollisionBehavior* instance = new EntityMovementCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityMovementCollisionBehavior::EntityMovementCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->movementCollision = nullptr;
	this->leftCollision = nullptr;
	this->rightCollision = nullptr;
	this->movementCollisionBound = false;
	this->submergeSound = WorldSound::create(SoundResources::Platformer_Environment_Splash1);
	this->emergeSound = WorldSound::create(SoundResources::Platformer_Environment_Emerge1);
	this->noEmergeSubmergeSoundCooldown = 1.0f;
	this->groundCollision = nullptr;
	this->headCollision = nullptr;
	this->movementBehavior = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->toggleQueryable(false);

	this->addChild(this->submergeSound);
	this->addChild(this->emergeSound);
}

EntityMovementCollisionBehavior::~EntityMovementCollisionBehavior()
{
	if (this->movementCollision != nullptr && this->movementCollision->getParent() != nullptr && this->movementCollision->getParent() != this)
	{
		this->movementCollision->getParent()->removeChild(this->movementCollision);
	}
}

void EntityMovementCollisionBehavior::onLoad()
{
	this->defer([=]()
	{
		this->buildMovementCollision();
		this->buildWallDetectors();
		this->toggleQueryable(true);
	});
	
	this->entity->watchForAttachedBehavior<EntityMovementBehavior>([=](EntityMovementBehavior* movementBehavior)
	{
		this->movementBehavior = movementBehavior;
	});
	
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

	this->entity->watchForAttachedBehavior<EntityGroundCollisionBehavior>([=](EntityGroundCollisionBehavior* groundCollision)
	{
		this->groundCollision = groundCollision;
	});

	this->entity->watchForAttachedBehavior<EntityHeadCollisionBehavior>([=](EntityHeadCollisionBehavior* headCollision)
	{
		this->headCollision = headCollision;
	});

	this->scheduleUpdate();
}

void EntityMovementCollisionBehavior::warpToPosition(Vec3 position, bool warpCamera)
{
	// Watch for own attached behavior -- this is to stall if this object is not queryable yet (and thus collision is not built yet)
	this->entity->watchForAttachedBehavior<EntityMovementCollisionBehavior>([=](EntityMovementCollisionBehavior* behavior)
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

void EntityMovementCollisionBehavior::onDisable()
{
	super::onDisable();
	
	if (this->movementCollision != nullptr)
	{
		this->movementCollision->setPhysicsEnabled(false);
	}
}

void EntityMovementCollisionBehavior::update(float dt)
{
	super::update(dt);

	if (this->noEmergeSubmergeSoundCooldown > 0.0f)
	{
		this->noEmergeSubmergeSoundCooldown -= dt;
	}

	this->tryBind();
}

void EntityMovementCollisionBehavior::enableNormalPhysics()
{
	this->movementCollision->setGravityEnabled(true);
	this->movementCollision->setVerticalDampening(CollisionObject::DefaultVerticalDampening);
}

void EntityMovementCollisionBehavior::enableWaterPhysics()
{
	this->movementCollision->setGravityEnabled(false);
	this->movementCollision->setVerticalDampening(EntityMovementCollisionBehavior::SwimVerticalDrag);
}

Vec2 EntityMovementCollisionBehavior::getVelocity()
{
	return this->movementCollision == nullptr ? Vec2::ZERO : this->movementCollision->getVelocity();
}

void EntityMovementCollisionBehavior::setVelocity(Vec2 velocity)
{
	if (this->movementCollision == nullptr)
	{
		return;
	}

	this->movementCollision->setVelocity(velocity);
}

bool EntityMovementCollisionBehavior::hasLeftWallCollision()
{
	return this->leftCollision == nullptr ? false : !this->leftCollision->getCurrentCollisions().empty();
}

bool EntityMovementCollisionBehavior::hasRightWallCollision()
{
	return this->rightCollision == nullptr ? false : !this->rightCollision->getCurrentCollisions().empty();
}

bool EntityMovementCollisionBehavior::hasLeftWallCollisionWith(CollisionObject* collisonObject)
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

bool EntityMovementCollisionBehavior::hasRightWallCollisionWith(CollisionObject* collisonObject)
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

void EntityMovementCollisionBehavior::buildMovementCollision()
{
	if (this->movementCollision != nullptr)
	{
		return;
	}

	CollisionType collisionType = CollisionType(PlatformerCollisionType::Movement);

	if (dynamic_cast<Squally*>(this->entity) != nullptr)
	{
		collisionType = CollisionType(PlatformerCollisionType::PlayerMovement);
	}

	this->movementCollision = CollisionObject::create(
		CollisionObject::createBox(this->entity->getMovementSize()),
		// CollisionObject::createCapsulePolygon(this->entity->getMovementSize(), 8.0f),
		collisionType,
		CollisionObject::Properties(true, false),
		Color4F::BLUE
	);
	
	if (dynamic_cast<Squally*>(this->entity) != nullptr)
	{
		this->movementCollision->setName("squally movement");
	}
	else
	{
		this->movementCollision->setName("entity movement");
	}

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);

	this->movementCollision->setPosition(offset);

	this->addChild(this->movementCollision);

	this->movementCollision->whileCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
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
		if (this->groundCollision != nullptr && !this->groundCollision->isOnGround() && this->noEmergeSubmergeSoundCooldown <= 0.0f && !this->submergeSound->isPlaying())
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

		if (this->groundCollision != nullptr && !this->groundCollision->isOnGround() && this->noEmergeSubmergeSoundCooldown <= 0.0f && !this->emergeSound->isPlaying())
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
			this->movementCollision->setVelocity(Vec2(this->movementCollision->getVelocity().x, EntityMovementCollisionBehavior::WaterJumpVelocity));

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
}

void EntityMovementCollisionBehavior::buildWallDetectors()
{
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

void EntityMovementCollisionBehavior::tryBind()
{
	if (this->movementCollision != nullptr && !this->movementCollisionBound)
	{
		this->movementCollisionBound = true;
		this->movementCollision->bindTo(this->entity);
	}
}
