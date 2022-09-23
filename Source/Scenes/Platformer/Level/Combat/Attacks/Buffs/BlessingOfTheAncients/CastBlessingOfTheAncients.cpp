#include "CastBlessingOfTheAncients.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/BlessingOfTheAncients/BlessingOfTheAncients.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastBlessingOfTheAncients* CastBlessingOfTheAncients::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastBlessingOfTheAncients* instance = new CastBlessingOfTheAncients(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastBlessingOfTheAncients::CastBlessingOfTheAncients(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_SwordGlowGreen, priority, AbilityType::Physical, 0, 0, 3, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastBlessingOfTheAncients::~CastBlessingOfTheAncients()
{
}

void CastBlessingOfTheAncients::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastBlessingOfTheAncients::cloneInternal()
{
	return CastBlessingOfTheAncients::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastBlessingOfTheAncients::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_BlessingOfTheAncients::create();
}

std::string CastBlessingOfTheAncients::getAttackAnimation()
{
	return "AttackCast";
}

void CastBlessingOfTheAncients::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(BlessingOfTheAncients::create(owner, next));
		});
	}
}

void CastBlessingOfTheAncients::onCleanup()
{
}

bool CastBlessingOfTheAncients::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<BlessingOfTheAncients>([&](BlessingOfTheAncients* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastBlessingOfTheAncients::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
