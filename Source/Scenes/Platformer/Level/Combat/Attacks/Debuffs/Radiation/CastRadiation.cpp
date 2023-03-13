#include "CastRadiation.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Radiation/Radiation.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastRadiation* CastRadiation::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastRadiation* instance = new CastRadiation(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastRadiation::CastRadiation(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_Radiation, priority, AbilityType::Nature, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Curse1);

	this->addChild(this->castSound);
}

CastRadiation::~CastRadiation()
{
}

void CastRadiation::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastRadiation::cloneInternal()
{
	return CastRadiation::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastRadiation::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_Radiation_Radiation::create();
}

std::string CastRadiation::getAttackAnimation()
{
	return "AttackCast";
}

void CastRadiation::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Radiation::create(owner, next));
		});
	}
}

void CastRadiation::onCleanup()
{
}

bool CastRadiation::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
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
			entityBuffBehavior->getBuff<Radiation>([&](Radiation* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastRadiation::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = CombatUtils::HasDuplicateCastOnLivingTarget(caster, target, [](PlatformerAttack* next) { return dynamic_cast<CastRadiation*>(next) != nullptr;  }) ? 0.0f : 1.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Radiation>([&](Radiation* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
