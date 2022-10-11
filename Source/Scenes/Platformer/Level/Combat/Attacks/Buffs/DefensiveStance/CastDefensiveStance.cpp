#include "CastDefensiveStance.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/DefensiveStance/DefensiveStance.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastDefensiveStance* CastDefensiveStance::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastDefensiveStance* instance = new CastDefensiveStance(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastDefensiveStance::CastDefensiveStance(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_ShieldGlowRed, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastDefensiveStance::~CastDefensiveStance()
{
}

void CastDefensiveStance::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastDefensiveStance::cloneInternal()
{
	return CastDefensiveStance::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastDefensiveStance::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_DefensiveStance::create();
}

std::string CastDefensiveStance::getAttackAnimation()
{
	return "AttackCast";
}

void CastDefensiveStance::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(DefensiveStance::create(owner, next));
		});
	}
}

void CastDefensiveStance::onCleanup()
{
}

bool CastDefensiveStance::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<DefensiveStance>([&](DefensiveStance* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastDefensiveStance::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
