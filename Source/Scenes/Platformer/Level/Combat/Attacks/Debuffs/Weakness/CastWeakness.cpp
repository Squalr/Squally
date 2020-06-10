#include "CastWeakness.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Weakness/Weakness.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastWeakness* CastWeakness::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastWeakness* instance = new CastWeakness(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastWeakness::CastWeakness(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_SwordBroken, priority, 0, 0, 6, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastWeakness::~CastWeakness()
{
}

void CastWeakness::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastWeakness::cloneInternal()
{
	return CastWeakness::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastWeakness::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_Weakness_Weakness::create();
}

std::string CastWeakness::getAttackAnimation()
{
	return "AttackCast";
}

void CastWeakness::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Weakness::create(owner, next));
		});
	}
}

void CastWeakness::onCleanup()
{
}

bool CastWeakness::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Weakness>([&](Weakness* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastWeakness::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
