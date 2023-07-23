#include "GoblinShamanOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinShaman.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Projectiles/Enemy/OverworldShadowBolt.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string GoblinShamanOutOfCombatAttackBehavior::MapKey = "goblin-shaman-attack";

GoblinShamanOutOfCombatAttackBehavior* GoblinShamanOutOfCombatAttackBehavior::create(GameObject* owner)
{
	GoblinShamanOutOfCombatAttackBehavior* instance = new GoblinShamanOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

GoblinShamanOutOfCombatAttackBehavior::GoblinShamanOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->goblinShaman = dynamic_cast<PlatformerEnemy*>(owner);
	this->shadowBolt = SmartAnimationSequenceNode::create();

	if (this->goblinShaman == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->shadowBolt);
}

GoblinShamanOutOfCombatAttackBehavior::~GoblinShamanOutOfCombatAttackBehavior()
{
}

void GoblinShamanOutOfCombatAttackBehavior::onLoad()
{
	super::onLoad();

	this->goblinShaman->watchForComponent<AgroBehavior>([=](AgroBehavior* agroBehavior)
	{
		this->agroBehavior = agroBehavior;

		this->agroBehavior->toggleChaseOnAgro(false);
	});

	this->scheduleUpdate();
}

void GoblinShamanOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void GoblinShamanOutOfCombatAttackBehavior::update(float dt)
{
	super::update(dt);

	if (this->agroBehavior != nullptr && this->agroBehavior->hasAgro())
	{
		this->attack();
	}
}


std::string GoblinShamanOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "AttackCast";
}

std::string GoblinShamanOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Physical_Punches_PunchWoosh1;
}

float GoblinShamanOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.2f;
}

float GoblinShamanOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

float GoblinShamanOutOfCombatAttackBehavior::getOutOfCombatAttackCooldown()
{
	return 3.5f;
}

float GoblinShamanOutOfCombatAttackBehavior::getProjectileLifetime()
{
	return 3.0f;
}

Projectile* GoblinShamanOutOfCombatAttackBehavior::createProjectile()
{
	if (this->goblinShaman == nullptr || this->agroBehavior == nullptr || this->agroBehavior->getAgroTarget() == nullptr)
	{
		return nullptr;
	}

	OverworldShadowBolt* projectile = OverworldShadowBolt::create();
	
	shadowBolt->setPosition3D(Vec3((this->goblinShaman->isFlippedX() ? -276.0f : 276.0f), 144.0f, 0.0f));
	
	projectile->setMovementMode(Projectile::MovementMode::RotationVelocity);
	projectile->setProjectileRotation(this->goblinShaman->isFlippedX() ? 180.0f + -10.0f : 10.0f);

	return projectile;
}
