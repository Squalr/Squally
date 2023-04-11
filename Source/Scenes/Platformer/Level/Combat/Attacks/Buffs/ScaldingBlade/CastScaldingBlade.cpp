#include "CastScaldingBlade.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ScaldingBlade/ScaldingBlade.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastScaldingBlade* CastScaldingBlade::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastScaldingBlade* instance = new CastScaldingBlade(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastScaldingBlade::CastScaldingBlade(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_AxeGlowRed, priority, AbilityType::Fire, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastScaldingBlade::~CastScaldingBlade()
{
}

void CastScaldingBlade::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastScaldingBlade::cloneInternal()
{
	return CastScaldingBlade::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastScaldingBlade::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_ScaldingBlade::create();
}

std::string CastScaldingBlade::getAttackAnimation()
{
	return "AttackCast";
}

void CastScaldingBlade::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(ScaldingBlade::create(owner, next));
		});
	}
}

void CastScaldingBlade::onCleanup()
{
}

bool CastScaldingBlade::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<ScaldingBlade>([&](ScaldingBlade* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastScaldingBlade::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
