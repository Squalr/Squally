#include "MainhandThrowOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string MainhandThrowOutOfCombatAttackBehavior::MapKey = "mainhand-throw";

MainhandThrowOutOfCombatAttackBehavior* MainhandThrowOutOfCombatAttackBehavior::create(GameObject* owner)
{
	MainhandThrowOutOfCombatAttackBehavior* instance = new MainhandThrowOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

MainhandThrowOutOfCombatAttackBehavior::MainhandThrowOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->owner = dynamic_cast<PlatformerEntity*>(owner);

	if (this->owner == nullptr)
	{
		this->invalidate();
	}
}

MainhandThrowOutOfCombatAttackBehavior::~MainhandThrowOutOfCombatAttackBehavior()
{
}

void MainhandThrowOutOfCombatAttackBehavior::onLoad()
{
	super::onLoad();

	this->owner->watchForComponent<AgroBehavior>([=](AgroBehavior* agroBehavior)
	{
		this->agroBehavior = agroBehavior;
		this->agroBehavior->toggleChaseOnAgro(false);
	});

	this->scheduleUpdate();
}

void MainhandThrowOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void MainhandThrowOutOfCombatAttackBehavior::update(float dt)
{
	super::update(dt);

	if (this->agroBehavior != nullptr && this->agroBehavior->hasAgro())
	{
		this->attack();
	}
}

std::string MainhandThrowOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "AttackThrow";
}

std::string MainhandThrowOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Physical_Projectiles_Woosh5;
}

float MainhandThrowOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.6f;
}

float MainhandThrowOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

float MainhandThrowOutOfCombatAttackBehavior::getOutOfCombatAttackCooldown()
{
	return 3.5f;
}

float MainhandThrowOutOfCombatAttackBehavior::getProjectileLifetime()
{
	return 3.0f;
}

Projectile* MainhandThrowOutOfCombatAttackBehavior::createProjectile()
{
	if (this->owner == nullptr || this->agroBehavior == nullptr || this->agroBehavior->getAgroTarget() == nullptr)
	{
		return nullptr;
	}
	
	ThrownObject* projectile = ThrownObject::create(this->owner, this->agroBehavior->getAgroTarget(), false, this->getMainhandResource(), CSize(64.0f, 128.0f));

	this->replaceAnimationPartWithProjectile("mainhand", projectile);

	this->agroBehavior->getAgroTarget()->getComponent<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
	{
		projectile->launchTowardsTarget3D(behavior->getTarget(), Vec2::ZERO, 2.0f, Vec3(0.75f, 0.75f, 0.75f));
	});

	return projectile;
}
