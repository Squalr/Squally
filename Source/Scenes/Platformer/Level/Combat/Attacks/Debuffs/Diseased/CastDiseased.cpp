#include "CastDiseased.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Diseased/Diseased.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastDiseased* CastDiseased::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastDiseased* instance = new CastDiseased(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastDiseased::CastDiseased(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_PurpleScarabShell, priority, AbilityType::Physical, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastDiseased::~CastDiseased()
{
}

void CastDiseased::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastDiseased::cloneInternal()
{
	return CastDiseased::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastDiseased::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_Diseased_Diseased::create();
}

std::string CastDiseased::getAttackAnimation()
{
	return "AttackCast";
}

void CastDiseased::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Diseased::create(owner, next));
		});
	}
}

void CastDiseased::onCleanup()
{
}

bool CastDiseased::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}
		
		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastDiseased*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<Diseased>([&](Diseased* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastDiseased::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Diseased>([&](Diseased* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
