#include "BirdBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
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
	this->hitDelay = 0.0f;
	this->startledSound = WorldSound::create();
	this->squawkSound = WorldSound::create();

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->startledSound);
	this->addChild(this->squawkSound);
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
	
	this->entity->watchForComponent<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* collisionBehavior)
	{
		if (collisionBehavior->entityCollision != nullptr && collisionBehavior->movementCollision != nullptr)
		{
			collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
			{
				this->onHit(collisionBehavior);
				return CollisionResult::CollideWithPhysics;
			});
		}
	});

	this->tryNextAction();
	this->scheduleUpdate();
}

void BirdBehavior::onDisable()
{
	super::onDisable();
}

void BirdBehavior::update(float dt)
{
	super::update(dt);

	this->hitDelay -= dt;
}

void BirdBehavior::tryNextAction()
{
	static int SoundIndex = 0;

	if (this->wasStartled)
	{
		return;
	}

	float randomNumber = RandomHelper::random_real(0.0f, 1.0f);

	if (randomNumber > 0.5f)
	{
		if (AnimationPart* beakBone = this->entity->getAnimations()->getAnimationPart("beak_bone"))
		{
			beakBone->reattachToTimeline();
		}

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
		switch(SoundIndex++ % 5)
		{
			default: case 0: this->squawkSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Squawk1); break;
			case 1: this->squawkSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Squawk2); break;
			case 2: this->squawkSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Squawk3); break;
			case 3: this->squawkSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Squawk4); break;
			case 4: this->squawkSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Squawk5); break;
		}

		this->moveBeak(0.5f);
		this->squawkSound->play();
		
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
		DelayTime::create(RandomHelper::random_real(0.2f, 5.0f)),
		CallFunc::create([=]()
		{
			tryNextAction();
		}),
		nullptr
	));
}

void BirdBehavior::onHit(EntityCollisionBehaviorBase* collisionBehavior)
{
	static int StartledIndex = 0;
	static const float HitCooldown = 0.5f;

	if (this->hitDelay > 0.0f)
	{
		return;
	}

	switch(StartledIndex++ % 5)
	{
		default: case 0: this->startledSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Startled1); break;
		case 1: this->startledSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Startled2); break;
		case 2: this->startledSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Startled3); break;
		case 3: this->startledSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Startled4); break;
		case 4: this->startledSound->setSoundResource(SoundResources::Platformer_Entities_Seagull_Startled5); break;
	}

	this->startledSound->play();

	// Subsequent hits can't take advantage of the startle animation, so we can animate the mouth manually
	if (this->wasStartled)
	{
		this->moveBeak(HitCooldown);
	}

	if (this->wasStartled
		|| collisionBehavior == nullptr
		|| collisionBehavior->movementCollision == nullptr
		|| collisionBehavior->entityCollision == nullptr
		|| collisionBehavior->leftCollision == nullptr
		|| collisionBehavior->rightCollision == nullptr)
	{
		return;
	}
	
	Vec3 entityPosition = GameUtils::getWorldCoords3D(this->entity);
	Vec3 squallyPosition = GameUtils::getWorldCoords3D(this->squally);
	float movementX = entityPosition.x < squallyPosition.x ? -1.0f : 1.0f;

	collisionBehavior->movementCollision->setGravity(Vec2(0.0f, RandomHelper::random_real(356.0f, 512.0f)));
	collisionBehavior->movementCollision->setCollisionEnabled(false);
	collisionBehavior->leftCollision->setCollisionEnabled(false);
	collisionBehavior->rightCollision->setCollisionEnabled(false);

	this->entity->runAction(Sequence::create(
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			collisionBehavior->movementCollision->setGravity(Vec2(0.0f, -RandomHelper::random_real(112.0f, 128.0f)));
		}),
		DelayTime::create(3.5f),
		CallFunc::create([=]()
		{
			collisionBehavior->movementCollision->setGravity(Vec2(0.0f, RandomHelper::random_real(112.0f, 128.0f)));
		}),
		DelayTime::create(30.0f),
		CallFunc::create([=]()
		{
			this->entity->despawn();
		}),
		nullptr
	));

	this->entity->setState(StateKeys::CinematicSourceX, Value(entityPosition.x));
	this->entity->setState(StateKeys::CinematicDestinationX, Value(entityPosition.x + movementX * 65536.0f));

	this->entity->getComponent<EntityMovementBehavior>([=](EntityMovementBehavior* movementBehavior)
	{
		movementBehavior->setMoveAcceleration(12000.0f);
	});

	this->wasStartled = true;
	this->hitDelay = HitCooldown;
	this->entity->setState(StateKeys::CinematicHijacked, Value(true));

	this->entity->getAnimations()->playAnimation("Startled", SmartAnimationNode::AnimationPlayMode::Callback, SmartAnimationNode::AnimParams(1.0f, 0.5f, true), [=]()
	{
		this->entity->getAnimations()->playAnimation("Fly", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f, 0.5f, true));
	});
}

void BirdBehavior::moveBeak(float duration)
{
	if (AnimationPart* beakBone = this->entity->getAnimations()->getAnimationPart("beak_bone"))
	{
		float startRotation = beakBone->getRotationSpriter();
		float endRotation = beakBone->getRotationSpriter() + (this->entity->isFlippedX() ? -1.0f : 1.0f) * (5.0f * float (M_PI) / 180.0f);

		beakBone->stopAllActions();
		beakBone->runAction(Sequence::create(
			ActionFloat::create(duration / 2.0f, startRotation, endRotation, [=](float newRotation)
			{
				beakBone->setRotationSpriter(newRotation);
			}),
			ActionFloat::create(duration / 2.0f, endRotation, startRotation, [=](float newRotation)
			{
				beakBone->setRotationSpriter(newRotation);
			}),
			CallFunc::create([=]()
			{
				beakBone->reattachToTimeline();
			}),
			nullptr
		));
	}
}
