#include "OrcBomberOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcBomber.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Projectiles/Combat/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string OrcBomberOutOfCombatAttackBehavior::MapKey = "orc-bomber-attack";

OrcBomberOutOfCombatAttackBehavior* OrcBomberOutOfCombatAttackBehavior::create(GameObject* owner)
{
	OrcBomberOutOfCombatAttackBehavior* instance = new OrcBomberOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

OrcBomberOutOfCombatAttackBehavior::OrcBomberOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->orcBomber = dynamic_cast<OrcBomber*>(owner);
	this->fireBreath = SmartAnimationSequenceNode::create();
	this->agroBehavior = nullptr;

	if (this->orcBomber == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->fireBreath);
}

OrcBomberOutOfCombatAttackBehavior::~OrcBomberOutOfCombatAttackBehavior()
{
}

void OrcBomberOutOfCombatAttackBehavior::onLoad()
{
	super::onLoad();

	this->orcBomber->watchForAttachedBehavior<AgroBehavior>([=](AgroBehavior* agroBehavior)
	{
		this->agroBehavior = agroBehavior;

		this->agroBehavior->toggleChaseOnAgro(false);
	});

	this->scheduleUpdate();
}

void OrcBomberOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void OrcBomberOutOfCombatAttackBehavior::update(float dt)
{
	super::update(dt);

	if (this->agroBehavior != nullptr && this->agroBehavior->hasAgro())
	{
		this->attack();
	}
}

std::string OrcBomberOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "AttackThrow";
}

std::string OrcBomberOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Physical_Projectiles_WeaponThrow5;
}

float OrcBomberOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.2f;
}

float OrcBomberOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

float OrcBomberOutOfCombatAttackBehavior::getOutOfCombatAttackCooldown()
{
	return 3.5f;
}

float OrcBomberOutOfCombatAttackBehavior::getProjectileLifetime()
{
	return 3.0f;
}

Projectile* OrcBomberOutOfCombatAttackBehavior::createProjectile()
{
	if (this->orcBomber == nullptr || this->agroBehavior == nullptr || this->agroBehavior->getAgroTarget() == nullptr)
	{
		return nullptr;
	}
	
	ThrownObject* projectile = ThrownObject::create(this->orcBomber, this->agroBehavior->getAgroTarget(), false, this->getMainhandResource(), Size(64.0f, 128.0f));
	SmartAnimationSequenceNode* fire = SmartAnimationSequenceNode::create(FXResources::TorchFire_TorchFire_0000);

	projectile->addDecor(fire);

	fire->playAnimationRepeat(FXResources::TorchFire_TorchFire_0000, 0.05f);
	fire->setPosition(Vec2(0.0f, 56.0f));

	this->replaceAnimationPartWithProjectile("mainhand", projectile);

	this->agroBehavior->getAgroTarget()->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
	{
		projectile->launchTowardsTarget(behavior->getTarget(), Vec2::ZERO, 2.0f, Vec3(0.5f, 0.5f, 0.5f));
	});

	return projectile;
}
