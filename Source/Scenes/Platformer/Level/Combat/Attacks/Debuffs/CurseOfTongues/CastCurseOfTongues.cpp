#include "CastCurseOfTongues.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CurseOfTongues/CurseOfTongues.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastCurseOfTongues* CastCurseOfTongues::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastCurseOfTongues* instance = new CastCurseOfTongues(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastCurseOfTongues::CastCurseOfTongues(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_Voodoo, priority, 0, 0, 6, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Curse1);

	this->addChild(this->castSound);
}

CastCurseOfTongues::~CastCurseOfTongues()
{
}

void CastCurseOfTongues::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastCurseOfTongues::cloneInternal()
{
	return CastCurseOfTongues::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastCurseOfTongues::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_CurseOfTongues::create();
}

std::string CastCurseOfTongues::getAttackAnimation()
{
	return "AttackCast";
}

void CastCurseOfTongues::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(CurseOfTongues::create(owner, next));
		});
	}
}

void CastCurseOfTongues::onCleanup()
{
}

bool CastCurseOfTongues::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
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

		next->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<CurseOfTongues>([&](CurseOfTongues* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastCurseOfTongues::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<CurseOfTongues>([&](CurseOfTongues* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
