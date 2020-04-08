#include "CastStrength.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Strength/Strength.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastStrength* CastStrength::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastStrength* instance = new CastStrength(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastStrength::CastStrength(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Buff, UIResources::Menus_Icons_Clock, priority, 0, 0, 3, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal5);

	this->addChild(this->castSound);
}

CastStrength::~CastStrength()
{
}

void CastStrength::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastStrength::cloneInternal()
{
	return CastStrength::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastStrength::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Strength_Strength::create();
}

std::string CastStrength::getAttackAnimation()
{
	return "AttackCast";
}

void CastStrength::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Strength::create(owner, next));
		});
	}
}

void CastStrength::onCleanup()
{
}

bool CastStrength::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Strength>([&](Strength* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}
