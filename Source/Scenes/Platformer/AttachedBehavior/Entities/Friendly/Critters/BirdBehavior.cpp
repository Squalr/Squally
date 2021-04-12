#include "BirdBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BirdBehavior::MapKey = "bird";

BirdBehavior* BirdBehavior::create(GameObject* owner)
{
	BirdBehavior* instance = new BirdBehavior(owner);

	instance->autorelease();

	return instance;
}

BirdBehavior::BirdBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->wasStartled = false;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

BirdBehavior::~BirdBehavior()
{
}

void BirdBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
	
	this->entity->watchForAttachedBehavior<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* collisionBehavior)
	{
		if (collisionBehavior->entityCollision != nullptr && collisionBehavior->movementCollision != nullptr)
		{
			collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
			{
				Vec3 entityPosition = GameUtils::getWorldCoords3D(this->entity);
				Vec3 squallyPosition = GameUtils::getWorldCoords3D(this->squally);
				float movementX = entityPosition.x < squallyPosition.x ? -1.0f : 1.0f;

				collisionBehavior->movementCollision->setGravity(Vec2(0.0f, 480.0f));

				this->entity->setState(StateKeys::CinematicSourceX, Value(entityPosition.x));
				this->entity->setState(StateKeys::CinematicDestinationX, Value(entityPosition.x + movementX * 2048.0f));

				this->entity->getAttachedBehavior<EntityMovementBehavior>([=](EntityMovementBehavior* movementBehavior)
				{
					movementBehavior->setMoveAcceleration(12000.0f);
				});

				this->flyAway();
				return CollisionResult::CollideWithPhysics;
			});
		}
	});

	this->tryPeck();
}

void BirdBehavior::onDisable()
{
	super::onDisable();
}

void BirdBehavior::tryPeck()
{
	if (this->wasStartled)
	{
		return;
	}

	float randomNumber = RandomHelper::random_real(0.0f, 1.0f);

	if (randomNumber > 0.5f)
	{
		this->entity->setState(StateKeys::CinematicHijacked, Value(true));
		this->entity->getAnimations()->playAnimation(randomNumber > 0.25f ? "Peck" : "PeckSlow", SmartAnimationNode::AnimationPlayMode::Callback, SmartAnimationNode::AnimParams(0.5f, 0.5f, true), [=]()
		{
			this->entity->clearState(StateKeys::CinematicHijacked);
			this->entity->getAnimations()->playAnimation();
			this->queueNextAction();
		});
	}
	else
	{
		this->queueNextAction();
	}
}

void BirdBehavior::queueNextAction()
{
	if (this->wasStartled)
	{
		return;
	}

	this->runAction(Sequence::create(
		DelayTime::create(RandomHelper::random_real(0.0f, 5.0f)),
		CallFunc::create([=]()
		{
			tryPeck();
		}),
		nullptr
	));
}

void BirdBehavior::flyAway()
{
	this->wasStartled = true;
	this->entity->setState(StateKeys::CinematicHijacked, Value(true));

	this->entity->getAnimations()->playAnimation("Startled", SmartAnimationNode::AnimationPlayMode::Callback, SmartAnimationNode::AnimParams(1.0f, 0.5f, true), [=]()
	{
		this->entity->getAnimations()->playAnimation("Fly", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f, 0.5f, true));
	});
}
