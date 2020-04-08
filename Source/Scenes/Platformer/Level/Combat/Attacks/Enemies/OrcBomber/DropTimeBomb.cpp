#include "DropTimeBomb.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Projectiles/Combat/TimeBomb/TimeBomb.h"
#include "Objects/Platformer/Projectiles/Combat/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/TimeBomb/Bombed.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DropTimeBomb* DropTimeBomb::create(float attackDuration, float recoverDuration, Priority priority)
{
	DropTimeBomb* instance = new DropTimeBomb(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

DropTimeBomb::DropTimeBomb(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Damage, UIResources::Menus_Icons_Clock, priority, 450, 500, 12, attackDuration, recoverDuration)
{
}

DropTimeBomb::~DropTimeBomb()
{
}

PlatformerAttack* DropTimeBomb::cloneInternal()
{
	return DropTimeBomb::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* DropTimeBomb::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string DropTimeBomb::getAttackAnimation()
{
	return "DropTimeBomb";
}

void DropTimeBomb::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (auto next : targets)
	{
		TimeBomb* timeBomb = TimeBomb::create(owner, next, [=]()
		{
			CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, next, this->getRandomDamage()));
		});

		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
			owner,
			timeBomb,
			ObjectEvents::SpawnMethod::Above,
			ObjectEvents::PositionMode::Discard,
			[&]()
			{
			},
			[&]()
			{
			}
		));

		const float BombHeightHalf = 133.0f / 2.0f;
		const float ZDrawDepthOffset = 1.0f;

		Vec2 offset = next->getEntityBottomPoint() + Vec2(RandomHelper::random_real(-96.0f, 96.0f), BombHeightHalf);

		timeBomb->runSpawnFX();
		timeBomb->setPosition3D(GameUtils::getWorldCoords3D(next) + Vec3(offset.x, offset.y, ZDrawDepthOffset));
		
		next->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Bombed::create(owner, next));
		});
	}
}

bool DropTimeBomb::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int buffCount = 0;

	for (auto next : otherTeam)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<TimeBomb>([&](TimeBomb* bombed)
			{
				buffCount++;
			});
		});
	}

	return buffCount != otherTeam.size();
}

float DropTimeBomb::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = 1.0f;

	target->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Bombed>([&](Bombed* bombed)
		{
			utility = 0.0f;
		});
	});

	return utility;
}

void DropTimeBomb::onCleanup()
{
}
