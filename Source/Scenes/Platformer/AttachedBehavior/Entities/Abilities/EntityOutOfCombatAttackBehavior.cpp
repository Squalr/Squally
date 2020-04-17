#include "EntityOutOfCombatAttackBehavior.h"

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
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Projectiles/Projectile.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityWeaponCollisionBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

EntityOutOfCombatAttackBehavior::EntityOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->outOfCombatAttackDebug = Sprite::create(UIResources::Menus_Icons_Sword);
	this->attackSound = WorldSound::create();
	this->isPerformingOutOfCombatAttack = false;
	this->cachedProjectile = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->addChild(this->outOfCombatAttackDebug);
	this->addChild(this->attackSound);
}

EntityOutOfCombatAttackBehavior::~EntityOutOfCombatAttackBehavior()
{
}

void EntityOutOfCombatAttackBehavior::onEnter()
{
	super::onEnter();
}

void EntityOutOfCombatAttackBehavior::initializePositions()
{
	super::initializePositions();

	this->outOfCombatAttackDebug->setPosition(Vec2(0.0f, this->entity->getEntitySize().height + this->entity->getHoverHeight() / 2.0f + 64.0f));
}

void EntityOutOfCombatAttackBehavior::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);
}

void EntityOutOfCombatAttackBehavior::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->outOfCombatAttackDebug->setVisible(false);
}

void EntityOutOfCombatAttackBehavior::onLoad()
{
}

void EntityOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void EntityOutOfCombatAttackBehavior::attack()
{
	if (this->isPerformingOutOfCombatAttack || this->entity->getStateOrDefaultBool(StateKeys::CinematicHijacked, false))
	{
		return;
	}

	std::string attackAnimation = this->getOutOfCombatAttackAnimation();
	std::string soundResource = this->getOutOfCombatAttackSound();
	float onset = this->getOutOfCombatAttackOnset();
	float sustain = this->getOutOfCombatAttackSustain();
	float cooldown = this->getOutOfCombatAttackCooldown();

	this->isPerformingOutOfCombatAttack = true;

	this->entity->getAnimations()->clearAnimationPriority();
	this->entity->getAnimations()->playAnimation(attackAnimation, SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f, 0.5f, true));
	this->entity->watchForAttachedBehavior<EntityWeaponCollisionBehavior>([=](EntityWeaponCollisionBehavior* weaponBehavior)
	{
		this->runAction(Sequence::create(
			DelayTime::create(onset),
			CallFunc::create([=]()
			{
				if (this->isDeveloperModeEnabled())
				{
					this->outOfCombatAttackDebug->setVisible(true);
				}

				this->attackSound->setSoundResource(soundResource);
				this->attackSound->play();

				this->tryPerformShootProjectile();

				weaponBehavior->enable();
			}),
			// TODO: Possible improvement: No sustain/collision behavior if a projectile was thrown
			DelayTime::create(sustain),
			CallFunc::create([=]()
			{
				weaponBehavior->disable();
				this->outOfCombatAttackDebug->setVisible(false);
			}),
			DelayTime::create(cooldown),
			CallFunc::create([=]()
			{
				this->isPerformingOutOfCombatAttack = false;
			}),
			nullptr
		));
	});
}

std::string EntityOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "Attack";
}

std::string EntityOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Combat_Attacks_Physical_Punches_PunchWoosh1;
}

float EntityOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.2f;
}

float EntityOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

float EntityOutOfCombatAttackBehavior::getOutOfCombatAttackCooldown()
{
	return 0.0f;
}

std::string EntityOutOfCombatAttackBehavior::getMainhandResource()
{
	AnimationPart* weapon = this->entity->getAnimations()->getAnimationPart("mainhand");

	if (weapon != nullptr)
	{
		return weapon->getSpriteResource();
	}

	return "";
}

std::string EntityOutOfCombatAttackBehavior::getOffhandResource()
{
	AnimationPart* weapon = this->entity->getAnimations()->getAnimationPart("offhand");

	if (weapon != nullptr)
	{
		return weapon->getSpriteResource();
	}

	return "";
}

void EntityOutOfCombatAttackBehavior::replaceMainhandWithProjectile(Projectile* projectile)
{
	this->replaceAnimationPartWithProjectile("mainhand", projectile);
}

void EntityOutOfCombatAttackBehavior::replaceOffhandWithProjectile(Projectile* projectile)
{
	this->replaceAnimationPartWithProjectile("offhand", projectile);
}

void EntityOutOfCombatAttackBehavior::replaceAnimationPartWithProjectile(std::string animationPart, Projectile* projectile)
{
	AnimationPart* weapon = this->entity->getAnimations()->getAnimationPart(animationPart);

	if (weapon != nullptr)
	{
		weapon->replaceWithObject(projectile, 2.0f);
	}

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		this->entity,
		projectile,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Discard,
		[&]()
		{
		},
		[&]()
		{
		}
	));

	Node* reference = weapon == nullptr ? (Node*)this->entity : (Node*)weapon;
	float layerZ = GameUtils::getDepth(GameUtils::getFirstParentOfType<MapLayer>(reference));

	// Set the position to the reference object's position. Offset it by any layer positioning.
	projectile->setPosition3D(GameUtils::getWorldCoords3D(reference) - Vec3(0.0f, 0.0f, layerZ));
};

void EntityOutOfCombatAttackBehavior::tryPerformShootProjectile()
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

		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
			this,
			projectile,
			ObjectEvents::SpawnMethod::LayerBelow,
			ObjectEvents::PositionMode::SetToOwner,
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

	projectile->setProjectileRotation(this->entity->isFlippedX() ? 180.0f : 0.0f);
	projectile->enable(true);
	projectile->stopAllActions();
	projectile->runSpawnFX();

	const Vec2 FixedOffset = Vec2(64.0f, -32.0f);

	Vec2 entityCenter = this->entity->getEntityCenterPoint();
	Vec2 spawnOffset = Vec2(entityCenter.x + (this->entity->isFlippedX() ? -FixedOffset.x : FixedOffset.x), entityCenter.y + FixedOffset.y) + this->getProjectileSpawnOffset();

	GameUtils::setWorldCoords3D(projectile, GameUtils::getWorldCoords3D(this) + Vec3(spawnOffset.x, spawnOffset.y, 0.0f));

	projectile->runAction(Sequence::create(
		DelayTime::create(this->getProjectileLifetime()),
		CallFunc::create([=]()
		{
			projectile->disable(false);
		}),
		nullptr
	));
}

Projectile* EntityOutOfCombatAttackBehavior::createProjectile()
{
	return nullptr;
}

void EntityOutOfCombatAttackBehavior::decorateProjectile(Projectile* projectile)
{
}

Vec2 EntityOutOfCombatAttackBehavior::getProjectileSpawnOffset()
{
	return Vec2::ZERO;
}

float EntityOutOfCombatAttackBehavior::getProjectileLifetime()
{
	return 0.5f;
}
