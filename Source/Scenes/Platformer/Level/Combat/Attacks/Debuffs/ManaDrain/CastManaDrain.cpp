#include "CastManaDrain.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/ManaDrain/ManaDrain.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastManaDrain* CastManaDrain::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastManaDrain* instance = new CastManaDrain(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastManaDrain::CastManaDrain(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_ManaSkull, priority, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastManaDrain::~CastManaDrain()
{
}

void CastManaDrain::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastManaDrain::cloneInternal()
{
	return CastManaDrain::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastManaDrain::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_ManaDrain::create();
}

std::string CastManaDrain::getAttackAnimation()
{
	return "AttackCast";
}

void CastManaDrain::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(ManaDrain::create(owner, next));
		});
	}
}

void CastManaDrain::onCleanup()
{
}

bool CastManaDrain::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
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
			entityBuffBehavior->getBuff<ManaDrain>([&](ManaDrain* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastManaDrain::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<ManaDrain>([&](ManaDrain* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
