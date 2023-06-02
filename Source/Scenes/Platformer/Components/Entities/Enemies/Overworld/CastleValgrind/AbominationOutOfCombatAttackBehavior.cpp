#include "AbominationOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinShaman.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Projectiles/Enemy/OverworldBoomerang.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string AbominationOutOfCombatAttackBehavior::MapKey = "abomination-attack";

AbominationOutOfCombatAttackBehavior* AbominationOutOfCombatAttackBehavior::create(GameObject* owner)
{
	AbominationOutOfCombatAttackBehavior* instance = new AbominationOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

AbominationOutOfCombatAttackBehavior::AbominationOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->abomination = dynamic_cast<PlatformerEnemy*>(owner);

	if (this->abomination == nullptr)
	{
		this->invalidate();
	}
}

AbominationOutOfCombatAttackBehavior::~AbominationOutOfCombatAttackBehavior()
{
}

void AbominationOutOfCombatAttackBehavior::onLoad()
{
	super::onLoad();

	this->abomination->watchForComponent<AgroBehavior>([=](AgroBehavior* agroBehavior)
	{
		this->agroBehavior = agroBehavior;

		this->agroBehavior->toggleChaseOnAgro(false);
	});

	this->scheduleUpdate();
}

void AbominationOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void AbominationOutOfCombatAttackBehavior::update(float dt)
{
	super::update(dt);

	if (this->agroBehavior != nullptr && this->agroBehavior->hasAgro())
	{
		this->attack();
	}
}


std::string AbominationOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "AttackOverworld";
}

std::string AbominationOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Physical_Punches_PunchWoosh1;
}

float AbominationOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.5f;
}

float AbominationOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

float AbominationOutOfCombatAttackBehavior::getOutOfCombatAttackCooldown()
{
	return 3.5f;
}

float AbominationOutOfCombatAttackBehavior::getProjectileLifetime()
{
	return 3.0f;
}

Projectile* AbominationOutOfCombatAttackBehavior::createProjectile()
{
	if (this->abomination == nullptr || this->agroBehavior == nullptr || this->agroBehavior->getAgroTarget() == nullptr)
	{
		return nullptr;
	}

	OverworldBoomerang* projectile = OverworldBoomerang::create(this->abomination);
	
	projectile->setPosition3D(Vec3((this->abomination->isFlippedX() ? -276.0f : 276.0f), 144.0f, 0.0f));
	projectile->setMovementMode(Projectile::MovementMode::Kinematic);

	return projectile;
}
