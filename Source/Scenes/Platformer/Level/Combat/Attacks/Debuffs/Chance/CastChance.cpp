#include "CastChance.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Chance/Chance.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastChance* CastChance::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastChance* instance = new CastChance(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastChance::CastChance(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_SwordBrokenAlt, priority, AbilityType::Physical, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastChance::~CastChance()
{
}

void CastChance::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastChance::cloneInternal()
{
	return CastChance::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastChance::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_Chance_Chance::create();
}

std::string CastChance::getAttackAnimation()
{
	return "Attack";
}

void CastChance::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Chance::create(owner, next));
		});
	}
}

void CastChance::onCleanup()
{
}

bool CastChance::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}

		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastChance*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<Chance>([&](Chance* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastChance::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Chance>([&](Chance* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
