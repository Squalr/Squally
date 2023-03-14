#include "CastBloodBoil.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/BloodBoil/BloodBoil.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastBloodBoil* CastBloodBoil::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastBloodBoil* instance = new CastBloodBoil(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastBloodBoil::CastBloodBoil(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_SkullGlowRed, priority, AbilityType::Fire, 0, 0, 7, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastBloodBoil::~CastBloodBoil()
{
}

void CastBloodBoil::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastBloodBoil::cloneInternal()
{
	return CastBloodBoil::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastBloodBoil::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_BloodBoil_BloodBoil::create();
}

std::string CastBloodBoil::getAttackAnimation()
{
	return "AttackCast";
}

void CastBloodBoil::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(BloodBoil::create(owner, next));
		});
	}
}

void CastBloodBoil::onCleanup()
{
}

bool CastBloodBoil::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}

		if (CombatUtils::HasDuplicateCastOnLivingTarget(caster, next, [](PlatformerAttack* next) { return dynamic_cast<CastBloodBoil*>(next) != nullptr;  }))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<BloodBoil>([&](BloodBoil* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastBloodBoil::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<BloodBoil>([&](BloodBoil* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
