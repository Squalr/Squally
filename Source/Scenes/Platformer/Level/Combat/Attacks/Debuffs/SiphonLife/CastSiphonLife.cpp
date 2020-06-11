#include "CastSiphonLife.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/SiphonLife/SiphonLife.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastSiphonLife* CastSiphonLife::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastSiphonLife* instance = new CastSiphonLife(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastSiphonLife::CastSiphonLife(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_BloodGoblet, priority, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastSiphonLife::~CastSiphonLife()
{
}

void CastSiphonLife::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastSiphonLife::cloneInternal()
{
	return CastSiphonLife::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastSiphonLife::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_SiphonLife::create();
}

std::string CastSiphonLife::getAttackAnimation()
{
	return "AttackCast";
}

void CastSiphonLife::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(SiphonLife::create(owner, next));
		});
	}
}

void CastSiphonLife::onCleanup()
{
}

bool CastSiphonLife::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}

		next->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<SiphonLife>([&](SiphonLife* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastSiphonLife::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<SiphonLife>([&](SiphonLife* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
