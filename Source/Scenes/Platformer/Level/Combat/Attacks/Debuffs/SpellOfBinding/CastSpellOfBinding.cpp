#include "CastSpellOfBinding.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/SpellOfBinding/SpellOfBinding.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastSpellOfBinding* CastSpellOfBinding::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastSpellOfBinding* instance = new CastSpellOfBinding(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastSpellOfBinding::CastSpellOfBinding(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_Book, priority, AbilityType::Arcane, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastSpellOfBinding::~CastSpellOfBinding()
{
}

void CastSpellOfBinding::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastSpellOfBinding::cloneInternal()
{
	return CastSpellOfBinding::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastSpellOfBinding::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_SpellOfBinding::create();
}

std::string CastSpellOfBinding::getAttackAnimation()
{
	return "AttackCast";
}

void CastSpellOfBinding::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(SpellOfBinding::create(owner, next));
		});
	}
}

void CastSpellOfBinding::onCleanup()
{
}

bool CastSpellOfBinding::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (PlatformerEntity* next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}
		
		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastSpellOfBinding*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<SpellOfBinding>([&](SpellOfBinding* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastSpellOfBinding::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = CombatUtils::HasDuplicateCastOnLivingTarget(caster, target, [](PlatformerAttack* next) { return dynamic_cast<CastSpellOfBinding*>(next) != nullptr;  }) ? 0.0f : 1.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<SpellOfBinding>([&](SpellOfBinding* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
