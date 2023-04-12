#include "CastZombieGrasp.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/ZombieGrasp/ZombieGrasp.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastZombieGrasp* CastZombieGrasp::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastZombieGrasp* instance = new CastZombieGrasp(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastZombieGrasp::CastZombieGrasp(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_ZombieGrasp, priority, AbilityType::Shadow, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastZombieGrasp::~CastZombieGrasp()
{
}

void CastZombieGrasp::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastZombieGrasp::cloneInternal()
{
	return CastZombieGrasp::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastZombieGrasp::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_ZombieGrasp_ZombieGrasp::create();
}

std::string CastZombieGrasp::getAttackAnimation()
{
	return "AttackCast";
}

void CastZombieGrasp::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(ZombieGrasp::create(owner, next));
		});
	}
}

void CastZombieGrasp::onCleanup()
{
}

bool CastZombieGrasp::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (PlatformerEntity* next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}
		
		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastZombieGrasp*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<ZombieGrasp>([&](ZombieGrasp* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastZombieGrasp::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = CombatUtils::HasDuplicateCastOnLivingTarget(caster, target, [](PlatformerAttack* next) { return dynamic_cast<CastZombieGrasp*>(next) != nullptr;  }) ? 0.0f : 1.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<ZombieGrasp>([&](ZombieGrasp* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
