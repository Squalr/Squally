#include "CastPoisonedArrows.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/PoisonedArrows/PoisonedArrows.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastPoisonedArrows* CastPoisonedArrows::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastPoisonedArrows* instance = new CastPoisonedArrows(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastPoisonedArrows::CastPoisonedArrows(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_PoisonSpears, priority, AbilityType::Nature, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastPoisonedArrows::~CastPoisonedArrows()
{
}

void CastPoisonedArrows::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastPoisonedArrows::cloneInternal()
{
	return CastPoisonedArrows::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastPoisonedArrows::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_PoisonedArrows_PoisonedArrows::create();
}

std::string CastPoisonedArrows::getAttackAnimation()
{
	return "AttackCast";
}

void CastPoisonedArrows::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(PoisonedArrows::create(owner, next));
		});
	}
}

void CastPoisonedArrows::onCleanup()
{
}

bool CastPoisonedArrows::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<PoisonedArrows>([&](PoisonedArrows* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastPoisonedArrows::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = CombatUtils::HasDuplicateCastOnLivingTarget(caster, target, [](PlatformerAttack* next) { return dynamic_cast<CastPoisonedArrows*>(next) != nullptr;  }) ? 0.0f : 1.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<PoisonedArrows>([&](PoisonedArrows* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
