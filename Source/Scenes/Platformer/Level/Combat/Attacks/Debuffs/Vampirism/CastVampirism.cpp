#include "CastVampirism.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Vampirism/Vampirism.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastVampirism* CastVampirism::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastVampirism* instance = new CastVampirism(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastVampirism::CastVampirism(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_SkullAndCrossbones, priority, AbilityType::Physical, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastVampirism::~CastVampirism()
{
}

void CastVampirism::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastVampirism::cloneInternal()
{
	return CastVampirism::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastVampirism::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_Vampirism::create();
}

std::string CastVampirism::getAttackAnimation()
{
	return "AttackCast";
}

void CastVampirism::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Vampirism::create(owner, next));
		});
	}
}

void CastVampirism::onCleanup()
{
}

bool CastVampirism::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}
		
		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastVampirism*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<Vampirism>([&](Vampirism* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastVampirism::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Vampirism>([&](Vampirism* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
