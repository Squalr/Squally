#include "CastArcaneProtection.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ArcaneProtection/ArcaneProtection.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastArcaneProtection* CastArcaneProtection::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastArcaneProtection* instance = new CastArcaneProtection(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastArcaneProtection::CastArcaneProtection(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_ShieldGlowBlue, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastArcaneProtection::~CastArcaneProtection()
{
}

void CastArcaneProtection::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastArcaneProtection::cloneInternal()
{
	return CastArcaneProtection::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastArcaneProtection::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_ArcaneProtection_ArcaneProtection::create();
}

std::string CastArcaneProtection::getAttackAnimation()
{
	return "AttackCast";
}

void CastArcaneProtection::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(ArcaneProtection::create(owner, next));
		});
	}
}

void CastArcaneProtection::onCleanup()
{
}

bool CastArcaneProtection::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<ArcaneProtection>([&](ArcaneProtection* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastArcaneProtection::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
