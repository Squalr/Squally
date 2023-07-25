#include "CastHotPotato.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/HotPotato/HotPotato.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastHotPotato* CastHotPotato::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastHotPotato* instance = new CastHotPotato(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastHotPotato::CastHotPotato(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_HotPotato, priority, AbilityType::Fire, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastHotPotato::~CastHotPotato()
{
}

void CastHotPotato::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastHotPotato::cloneInternal()
{
	return CastHotPotato::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastHotPotato::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_HotPotato_HotPotato::create();
}

std::string CastHotPotato::getAttackAnimation()
{
	return "AttackCast";
}

void CastHotPotato::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(HotPotato::create(owner, next));
		});
	}
}

void CastHotPotato::onCleanup()
{
}

bool CastHotPotato::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (PlatformerEntity* next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}
		
		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastHotPotato*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<HotPotato>([&](HotPotato* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastHotPotato::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = CombatUtils::HasDuplicateCastOnLivingTarget(caster, target, [](PlatformerAttack* next) { return dynamic_cast<CastHotPotato*>(next) != nullptr;  }) ? 0.0f : 1.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<HotPotato>([&](HotPotato* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
