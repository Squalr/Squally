#include "CastSeekingBlade.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/SeekingBlade/SeekingBlade.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastSeekingBlade* CastSeekingBlade::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastSeekingBlade* instance = new CastSeekingBlade(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastSeekingBlade::CastSeekingBlade(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_DaggerGlowYellow, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastSeekingBlade::~CastSeekingBlade()
{
}

void CastSeekingBlade::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastSeekingBlade::cloneInternal()
{
	return CastSeekingBlade::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastSeekingBlade::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_SeekingBlade_SeekingBlade::create();
}

std::string CastSeekingBlade::getAttackAnimation()
{
	return "AttackCast";
}

void CastSeekingBlade::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(SeekingBlade::create(owner, next));
		});
	}
}

void CastSeekingBlade::onCleanup()
{
}

bool CastSeekingBlade::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<SeekingBlade>([&](SeekingBlade* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastSeekingBlade::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
