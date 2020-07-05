#include "CastSharpenedBlade.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/SharpenedBlade/SharpenedBlade.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastSharpenedBlade* CastSharpenedBlade::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastSharpenedBlade* instance = new CastSharpenedBlade(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastSharpenedBlade::CastSharpenedBlade(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_SwordAlt, priority, AbilityType::Physical, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastSharpenedBlade::~CastSharpenedBlade()
{
}

void CastSharpenedBlade::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastSharpenedBlade::cloneInternal()
{
	return CastSharpenedBlade::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastSharpenedBlade::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_SharpenedBlade::create();
}

std::string CastSharpenedBlade::getAttackAnimation()
{
	return "AttackCast";
}

void CastSharpenedBlade::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(SharpenedBlade::create(owner, next));
		});
	}
}

void CastSharpenedBlade::onCleanup()
{
}

bool CastSharpenedBlade::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<SharpenedBlade>([&](SharpenedBlade* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastSharpenedBlade::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
