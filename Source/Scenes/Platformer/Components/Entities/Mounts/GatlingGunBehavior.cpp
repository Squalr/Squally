#include "GatlingGunBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Interactables/Mounts/GatlingGun/GatlingGun.h"
#include "Objects/Platformer/Projectiles/GatlingGun/Shell.h"
#include "Objects/Platformer/Projectiles/Projectile.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/UnderflowRuins/KillingMachine/KillingMachineDamageBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/UnderflowRuins/KillingMachine/KillingMachineHealthBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GatlingGunBehavior::MapKey = "gatling-gun";

GatlingGunBehavior* GatlingGunBehavior::create(GameObject* owner)
{
	GatlingGunBehavior* instance = new GatlingGunBehavior(owner);

	instance->autorelease();

	return instance;
}

GatlingGunBehavior::GatlingGunBehavior(GameObject* owner) : super(owner)
{
	this->gatlingGun = dynamic_cast<GatlingGun*>(owner);
	this->attackSound = WorldSound::create();

	if (this->gatlingGun == nullptr)
	{
		this->invalidate();
	}
	
	this->addChild(this->attackSound);
}

GatlingGunBehavior::~GatlingGunBehavior()
{
}

void GatlingGunBehavior::onEnter()
{
	super::onEnter();
}

void GatlingGunBehavior::initializePositions()
{
	super::initializePositions();
}

void GatlingGunBehavior::onLoad()
{
	this->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (this->gatlingGun != nullptr && this->gatlingGun->isMounted())
		{
			this->attack();
		}
	});
}

void GatlingGunBehavior::onDisable()
{
	super::onDisable();
}

void GatlingGunBehavior::attack()
{
	if (this->isPerformingOutOfCombatAttack || this->gatlingGun->getRuntimeStateOrDefaultBool(StateKeys::CinematicHijacked, false))
	{
		return;
	}

	std::string attackAnimation = this->getOutOfCombatAttackAnimation();
	std::string soundResource = this->getOutOfCombatAttackSound();
	float onset = this->getOutOfCombatAttackOnset();
	float sustain = this->getOutOfCombatAttackSustain();
	float cooldown = this->getOutOfCombatAttackCooldown();

	this->isPerformingOutOfCombatAttack = true;

	this->gatlingGun->getAnimations()->clearAnimationPriority();
	this->gatlingGun->getAnimations()->playAnimation(attackAnimation, SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f, 0.5f, true));
	
	this->runAction(Sequence::create(
		DelayTime::create(onset),
		CallFunc::create([=]()
		{
			this->attackSound->setSoundResource(soundResource);
			this->attackSound->play();

			this->tryPerformShootProjectile();
		}),
		DelayTime::create(sustain),
		DelayTime::create(cooldown),
		CallFunc::create([=]()
		{
			this->isPerformingOutOfCombatAttack = false;
		}),
		nullptr
	));
}

std::string GatlingGunBehavior::getOutOfCombatAttackAnimation()
{
	return "Attack";
}

std::string GatlingGunBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Physical_Punches_PunchWoosh1;
}

float GatlingGunBehavior::getOutOfCombatAttackOnset()
{
	return 0.2f;
}

float GatlingGunBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

float GatlingGunBehavior::getOutOfCombatAttackCooldown()
{
	return 0.0f;
}

void GatlingGunBehavior::tryPerformShootProjectile()
{
	Projectile* projectile = this->createProjectile();

	if (projectile == nullptr)
	{
		return;
	}

	if (projectile != this->cachedProjectile)
	{
		this->decorateProjectile(projectile);

		if (this->cachedProjectile != nullptr && this->cachedProjectile->getParent() != nullptr)
		{
			this->cachedProjectile->getParent()->removeChild(this->cachedProjectile);
			this->cachedProjectile = nullptr;
		}

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			this,
			projectile,
			SpawnMethod::Above,
			PositionMode::SetToOwner,
			[&]()
			{
				this->cachedProjectile = projectile;
			},
			[&]()
			{
				projectile = nullptr;
			}
		));
	}
	
	projectile->enable(true);
	projectile->runSpawnFX();

	Vec2 spawnOffset = this->getProjectileSpawnOffset();

	GameUtils::setWorldCoords3D(projectile, GameUtils::getWorldCoords3D(this) + Vec3(spawnOffset.x, spawnOffset.y, 0.0f));

	const float FadeDuration = 0.15f;

	projectile->runAction(Sequence::create(
		DelayTime::create(std::max(this->getProjectileLifetime() - FadeDuration, 0.0f)),
		CallFunc::create([=]()
		{
			projectile->runAction(FadeTo::create(FadeDuration, 0));
		}),
		nullptr
	));

	projectile->runAction(Sequence::create(
		DelayTime::create(this->getProjectileLifetime()),
		CallFunc::create([=]()
		{
			projectile->disable(false);
		}),
		nullptr
	));
}

Projectile* GatlingGunBehavior::createProjectile()
{
	return Shell::create();
}

void GatlingGunBehavior::decorateProjectile(Projectile* projectile)
{
	projectile->whenCollidesWith({(int)PlatformerCollisionType::Entity }, [=](CollisionData collisionData)
	{
		PlatformerEntity* target = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other);

		if (target != nullptr)
		{
			target->getComponent<KillingMachineHealthBehavior>([target](KillingMachineHealthBehavior* healthBehavior)
			{
				target->getComponent<KillingMachineDamageBehavior>([target, healthBehavior](KillingMachineDamageBehavior* damageBehavior)
				{
					int damage = damageBehavior->compare();
					healthBehavior->addHealth(-damage);
				});
			});
		}
		return CollisionResult::DoNothing;
	});
}

Vec2 GatlingGunBehavior::getProjectileSpawnOffset()
{
	return Vec2(64.0f, 128.0f);
}

float GatlingGunBehavior::getProjectileLifetime()
{
	return 0.75f;
}
