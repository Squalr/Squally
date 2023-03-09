#include "CastFear.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Fear/Fear.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastFear* CastFear::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastFear* instance = new CastFear(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastFear::CastFear(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_Skull2, priority, AbilityType::Shadow, 0, 0, 11, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Curse1);

	this->addChild(this->castSound);
}

CastFear::~CastFear()
{
}

void CastFear::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastFear::cloneInternal()
{
	return CastFear::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastFear::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_Fear_Fear::create();
}

std::string CastFear::getAttackAnimation()
{
	return "AttackCast";
}

void CastFear::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Fear::create(owner, next));
		});
	}
}

void CastFear::onCleanup()
{
}

bool CastFear::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// This spell is horrible in a 1v2+ situation
	if (CombatUtils::GetLivingCount(sameTeam) <= 1 && CombatUtils::GetLivingCount(otherTeam) <= 2)
	{
		return false;
	}

	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastFear*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<Fear>([&](Fear* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastFear::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = CombatUtils::HasDuplicateCastOnLivingTarget(caster, target, [](PlatformerAttack* next) { return dynamic_cast<CastFear*>(next) != nullptr;  }) ? 0.0f : 1.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Fear>([&](Fear* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
