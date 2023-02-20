#include "CastUnholyProtection.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/UnholyProtection/UnholyProtection.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastUnholyProtection* CastUnholyProtection::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastUnholyProtection* instance = new CastUnholyProtection(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastUnholyProtection::CastUnholyProtection(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_ShieldGlowBlue, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastUnholyProtection::~CastUnholyProtection()
{
}

void CastUnholyProtection::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastUnholyProtection::cloneInternal()
{
	return CastUnholyProtection::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastUnholyProtection::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_UnholyProtection_UnholyProtection::create();
}

std::string CastUnholyProtection::getAttackAnimation()
{
	return "AttackCast";
}

void CastUnholyProtection::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(UnholyProtection::create(owner, next));
		});
	}
}

void CastUnholyProtection::onCleanup()
{
}

bool CastUnholyProtection::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<UnholyProtection>([&](UnholyProtection* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastUnholyProtection::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
