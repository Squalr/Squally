#include "CastHaste.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Haste/Haste.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastHaste* CastHaste::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastHaste* instance = new CastHaste(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastHaste::CastHaste(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_HourGlass, priority, 0, 0, 8, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastHaste::~CastHaste()
{
}

void CastHaste::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastHaste::cloneInternal()
{
	return CastHaste::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastHaste::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Haste_Haste::create();
}

std::string CastHaste::getAttackAnimation()
{
	return "AttackCast";
}

void CastHaste::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Haste::create(owner, next));
		});
	}
}

void CastHaste::onCleanup()
{
}

bool CastHaste::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Haste>([&](Haste* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastHaste::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
