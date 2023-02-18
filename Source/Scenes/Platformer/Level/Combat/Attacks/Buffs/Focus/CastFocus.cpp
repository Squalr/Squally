#include "CastFocus.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Focus/Focus.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastFocus* CastFocus::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastFocus* instance = new CastFocus(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastFocus::CastFocus(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_ShieldGlowBlue, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastFocus::~CastFocus()
{
}

void CastFocus::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastFocus::cloneInternal()
{
	return CastFocus::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastFocus::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Focus_Focus::create();
}

std::string CastFocus::getAttackAnimation()
{
	return "AttackCast";
}

void CastFocus::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Focus::create(owner, next));
		});
	}
}

void CastFocus::onCleanup()
{
}

bool CastFocus::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Focus>([&](Focus* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastFocus::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
