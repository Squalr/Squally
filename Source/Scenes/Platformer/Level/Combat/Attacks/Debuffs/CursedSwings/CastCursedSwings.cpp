#include "CastCursedSwings.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CursedSwings/CursedSwings.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastCursedSwings* CastCursedSwings::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastCursedSwings* instance = new CastCursedSwings(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastCursedSwings::CastCursedSwings(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_AxeGlowPurple, priority, AbilityType::Shadow, 0, 0, 6, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Curse1);

	this->addChild(this->castSound);
}

CastCursedSwings::~CastCursedSwings()
{
}

void CastCursedSwings::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastCursedSwings::cloneInternal()
{
	return CastCursedSwings::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastCursedSwings::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CursedSwings::create();
}

std::string CastCursedSwings::getAttackAnimation()
{
	return "AttackCast";
}

void CastCursedSwings::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(CursedSwings::create(owner, next));
		});
	}
}

void CastCursedSwings::onCleanup()
{
}

bool CastCursedSwings::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// This spell is horrible in a 1v2+ situation
	if (CombatUtils::GetLivingCount(sameTeam) <= 1 && CombatUtils::GetLivingCount(otherTeam) <= 2)
	{
		return false;
	}

	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}
		
		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastCursedSwings*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<CursedSwings>([&](CursedSwings* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastCursedSwings::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = CombatUtils::HasDuplicateCastOnLivingTarget(caster, target, [](PlatformerAttack* next) { return dynamic_cast<CastCursedSwings*>(next) != nullptr;  }) ? 0.0f : 1.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<CursedSwings>([&](CursedSwings* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
