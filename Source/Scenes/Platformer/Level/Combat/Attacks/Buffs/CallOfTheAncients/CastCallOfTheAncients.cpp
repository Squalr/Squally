#include "CastCallOfTheAncients.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/CallOfTheAncients/CallOfTheAncients.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastCallOfTheAncients* CastCallOfTheAncients::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastCallOfTheAncients* instance = new CastCallOfTheAncients(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastCallOfTheAncients::CastCallOfTheAncients(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_Gauntlet, priority, AbilityType::Physical, 0, 0, 3, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastCallOfTheAncients::~CastCallOfTheAncients()
{
}

void CastCallOfTheAncients::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastCallOfTheAncients::cloneInternal()
{
	return CastCallOfTheAncients::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastCallOfTheAncients::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_CallOfTheAncients_CallOfTheAncients::create();
}

std::string CastCallOfTheAncients::getAttackAnimation()
{
	return "AttackCast";
}

void CastCallOfTheAncients::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(CallOfTheAncients::create(owner, next));
		});
	}
}

void CastCallOfTheAncients::onCleanup()
{
}

bool CastCallOfTheAncients::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<CallOfTheAncients>([&](CallOfTheAncients* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastCallOfTheAncients::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
