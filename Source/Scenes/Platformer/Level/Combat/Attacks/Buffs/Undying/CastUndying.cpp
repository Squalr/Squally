#include "CastUndying.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Undying/Undying.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastUndying* CastUndying::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastUndying* instance = new CastUndying(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastUndying::CastUndying(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_Skull, priority, 0, 0, 8, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastUndying::~CastUndying()
{
}

void CastUndying::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastUndying::cloneInternal()
{
	return CastUndying::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastUndying::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Undying_Undying::create();
}

std::string CastUndying::getAttackAnimation()
{
	return "AttackCast";
}

void CastUndying::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");
	
	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Undying::create(owner, next));
		});
	}
}

void CastUndying::onCleanup()
{
}

bool CastUndying::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Undying>([&](Undying* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastUndying::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
