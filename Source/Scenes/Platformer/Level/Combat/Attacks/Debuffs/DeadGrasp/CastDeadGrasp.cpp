#include "CastDeadGrasp.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/DeadGrasp/DeadGrasp.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastDeadGrasp* CastDeadGrasp::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastDeadGrasp* instance = new CastDeadGrasp(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastDeadGrasp::CastDeadGrasp(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_EyeStrain, priority, AbilityType::Physical, 0, 0, 7, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastDeadGrasp::~CastDeadGrasp()
{
}

void CastDeadGrasp::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastDeadGrasp::cloneInternal()
{
	return CastDeadGrasp::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastDeadGrasp::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_DeadGrasp_DeadGrasp::create();
}

std::string CastDeadGrasp::getAttackAnimation()
{
	return "AttackCast";
}

void CastDeadGrasp::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(DeadGrasp::create(owner, next));
		});
	}
}

void CastDeadGrasp::onCleanup()
{
}

bool CastDeadGrasp::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
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
			entityBuffBehavior->getBuff<DeadGrasp>([&](DeadGrasp* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastDeadGrasp::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<DeadGrasp>([&](DeadGrasp* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
