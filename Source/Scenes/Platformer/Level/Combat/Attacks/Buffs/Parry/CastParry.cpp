#include "CastParry.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Parry/Parry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastParry* CastParry::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastParry* instance = new CastParry(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastParry::CastParry(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_ShieldAdorned, priority, AbilityType::Arcane, 0, 0, 8, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastParry::~CastParry()
{
}

void CastParry::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastParry::cloneInternal()
{
	return CastParry::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastParry::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Parry_Parry::create();
}

std::string CastParry::getAttackAnimation()
{
	return "AttackCast";
}

void CastParry::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());
	
	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Parry::create(owner, next));
		});
	}
}

void CastParry::onCleanup()
{
}

bool CastParry::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Parry>([&](Parry* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastParry::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
