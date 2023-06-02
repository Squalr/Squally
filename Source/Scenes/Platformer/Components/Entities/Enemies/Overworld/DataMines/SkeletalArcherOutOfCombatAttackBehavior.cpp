#include "SkeletalArcherOutOfCombatAttackBehavior.h"

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

const std::string SkeletalArcherOutOfCombatAttackBehavior::MapKey = "skeletal-archer-attack";

SkeletalArcherOutOfCombatAttackBehavior* SkeletalArcherOutOfCombatAttackBehavior::create(GameObject* owner)
{
	SkeletalArcherOutOfCombatAttackBehavior* instance = new SkeletalArcherOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

SkeletalArcherOutOfCombatAttackBehavior::SkeletalArcherOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->skeletalArcher = dynamic_cast<PlatformerEnemy*>(owner);

	if (this->skeletalArcher == nullptr)
	{
		this->invalidate();
	}
}

SkeletalArcherOutOfCombatAttackBehavior::~SkeletalArcherOutOfCombatAttackBehavior()
{
}

void SkeletalArcherOutOfCombatAttackBehavior::onLoad()
{
	super::onLoad();

	this->skeletalArcher->watchForComponent<AgroBehavior>([=](AgroBehavior* agroBehavior)
	{
		this->agroBehavior = agroBehavior;

		this->agroBehavior->toggleChaseOnAgro(false);
	});

	this->scheduleUpdate();
}

void SkeletalArcherOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void SkeletalArcherOutOfCombatAttackBehavior::update(float dt)
{
	super::update(dt);

	if (this->agroBehavior != nullptr && this->agroBehavior->hasAgro())
	{
		this->attack();
	}
}


std::string SkeletalArcherOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "AttackOverworld";
}

std::string SkeletalArcherOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Physical_Punches_PunchWoosh1;
}

float SkeletalArcherOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.5f;
}

float SkeletalArcherOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

float SkeletalArcherOutOfCombatAttackBehavior::getOutOfCombatAttackCooldown()
{
	return 3.5f;
}

float SkeletalArcherOutOfCombatAttackBehavior::getProjectileLifetime()
{
	return 3.0f;
}

Projectile* SkeletalArcherOutOfCombatAttackBehavior::createProjectile()
{
	if (this->skeletalArcher == nullptr || this->agroBehavior == nullptr || this->agroBehavior->getAgroTarget() == nullptr)
	{
		return nullptr;
	}

	OverworldArrow* projectile = OverworldArrow::create(this->skeletalArcher, EntityResources::Enemies_DataMines_SkeletalArcher_ARROW);
	
	projectile->setPosition3D(Vec3((this->skeletalArcher->isFlippedX() ? -276.0f : 276.0f), 144.0f, 0.0f));
	projectile->setMovementMode(Projectile::MovementMode::Kinematic);

	return projectile;
}
