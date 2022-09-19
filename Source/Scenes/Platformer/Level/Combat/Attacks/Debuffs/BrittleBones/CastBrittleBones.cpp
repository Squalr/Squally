#include "CastBrittleBones.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/BrittleBones/BrittleBones.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastBrittleBones* CastBrittleBones::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastBrittleBones* instance = new CastBrittleBones(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastBrittleBones::CastBrittleBones(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_RunePurple, priority, AbilityType::Physical, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastBrittleBones::~CastBrittleBones()
{
}

void CastBrittleBones::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastBrittleBones::cloneInternal()
{
	return CastBrittleBones::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastBrittleBones::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_BrittleBones_BrittleBones::create();
}

std::string CastBrittleBones::getAttackAnimation()
{
	return "AttackCast";
}

void CastBrittleBones::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(BrittleBones::create(owner, next));
		});
	}
}

void CastBrittleBones::onCleanup()
{
}

bool CastBrittleBones::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
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
			entityBuffBehavior->getBuff<BrittleBones>([&](BrittleBones* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastBrittleBones::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<BrittleBones>([&](BrittleBones* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
