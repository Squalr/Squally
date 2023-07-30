#include "DemonArcherOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinShaman.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Projectiles/Enemy/OverworldArrow.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string DemonArcherOutOfCombatAttackBehavior::MapKey = "demon-archer-attack";

DemonArcherOutOfCombatAttackBehavior* DemonArcherOutOfCombatAttackBehavior::create(GameObject* owner)
{
	DemonArcherOutOfCombatAttackBehavior* instance = new DemonArcherOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

DemonArcherOutOfCombatAttackBehavior::DemonArcherOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->demonArcher = dynamic_cast<PlatformerEnemy*>(owner);

	if (this->demonArcher == nullptr)
	{
		this->invalidate();
	}
}

DemonArcherOutOfCombatAttackBehavior::~DemonArcherOutOfCombatAttackBehavior()
{
}

void DemonArcherOutOfCombatAttackBehavior::onLoad()
{
	super::onLoad();

	this->demonArcher->watchForComponent<AgroBehavior>([=](AgroBehavior* agroBehavior)
	{
		this->agroBehavior = agroBehavior;

		this->agroBehavior->toggleChaseOnAgro(false);
	});

	this->scheduleUpdate();
}

void DemonArcherOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void DemonArcherOutOfCombatAttackBehavior::update(float dt)
{
	super::update(dt);

	if (this->agroBehavior != nullptr && this->agroBehavior->hasAgro())
	{
		this->attack();
	}
}


std::string DemonArcherOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "AttackOverworld";
}

std::string DemonArcherOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Physical_Punches_PunchWoosh1;
}

float DemonArcherOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.5f;
}

float DemonArcherOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

float DemonArcherOutOfCombatAttackBehavior::getOutOfCombatAttackCooldown()
{
	return 3.5f;
}

float DemonArcherOutOfCombatAttackBehavior::getProjectileLifetime()
{
	return 3.0f;
}

Vec2 DemonArcherOutOfCombatAttackBehavior::getProjectileSpawnOffset()
{
	if (this->demonArcher != nullptr)
	{
		return Vec2(this->demonArcher->isFlippedX() ? -128.0f : 128.0f, -8.0f);
	}

	return Vec2::ZERO;
}

Projectile* DemonArcherOutOfCombatAttackBehavior::createProjectile()
{
	if (this->demonArcher == nullptr || this->agroBehavior == nullptr || this->agroBehavior->getAgroTarget() == nullptr)
	{
		return nullptr;
	}

	OverworldArrow* projectile = OverworldArrow::create(this->demonArcher, EntityResources::Enemies_FirewallFissure_DemonArcher_ARROW_2, 0.0f);
	
	projectile->setMovementMode(Projectile::MovementMode::Kinematic);

	return projectile;
}
