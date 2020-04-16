#include "GroggOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Enemies/EndianForest/KingGrogg.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Projectiles/Enemy/OverworldFireball.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FxResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string GroggOutOfCombatAttackBehavior::MapKey = "king-grogg-attack";

GroggOutOfCombatAttackBehavior* GroggOutOfCombatAttackBehavior::create(GameObject* owner)
{
	GroggOutOfCombatAttackBehavior* instance = new GroggOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

GroggOutOfCombatAttackBehavior::GroggOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->kingGrogg = dynamic_cast<KingGrogg*>(owner);
	this->projectile = nullptr;
	this->fireBreath = SmartAnimationSequenceNode::create();

	if (this->kingGrogg == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->fireBreath);
}

GroggOutOfCombatAttackBehavior::~GroggOutOfCombatAttackBehavior()
{
}

void GroggOutOfCombatAttackBehavior::onLoad()
{
	super::onLoad();
}

void GroggOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void GroggOutOfCombatAttackBehavior::attack()
{
	this->doOutOfCombatAttack(this->getOutOfCombatAttackAnimation(), this->getOutOfCombatAttackSound(), this->getOutOfCombatAttackOnset(), this->getOutOfCombatAttackSustain());
}

std::string GroggOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "AttackDragon";
}

std::string GroggOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Combat_Attacks_Physical_Punches_PunchWoosh1;
}

float GroggOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.2f;
}

float GroggOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 0.15f;
}

Projectile* GroggOutOfCombatAttackBehavior::createProjectile()
{
	if (this->kingGrogg == nullptr)
	{
		return nullptr;
	}

	OverworldFireball* projectile = OverworldFireball::create();
	
	fireBreath->setPosition3D(Vec3((this->kingGrogg->isFlippedX() ? -276.0f : 276.0f), 144.0f, 0.0f));
	fireBreath->playAnimation(FXResources::FireBreath_FireBreath_0000, 0.05f, true);
	fireBreath->setFlippedX(this->kingGrogg->isFlippedX());

	projectile->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		if (!this->kingGrogg->getStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		Squally* squally = GameUtils::getFirstParentOfType<Squally>(collisionData.other);

		if (squally != nullptr && squally->getStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			// Encountered enemy w/ first-strike
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->kingGrogg, false));
		}

		projectile->runImpactFX();

		return CollisionObject::CollisionResult::DoNothing;
	});

	return projectile;
}
