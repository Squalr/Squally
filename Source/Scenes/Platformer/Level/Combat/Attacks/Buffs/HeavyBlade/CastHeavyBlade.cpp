#include "CastHeavyBlade.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/HeavyBlade/HeavyBlade.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastHeavyBlade* CastHeavyBlade::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastHeavyBlade* instance = new CastHeavyBlade(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastHeavyBlade::CastHeavyBlade(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_Shovel, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastHeavyBlade::~CastHeavyBlade()
{
}

void CastHeavyBlade::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastHeavyBlade::cloneInternal()
{
	return CastHeavyBlade::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastHeavyBlade::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_HeavyBlade::create();
}

std::string CastHeavyBlade::getAttackAnimation()
{
	return "AttackCast";
}

void CastHeavyBlade::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(HeavyBlade::create(owner, next));
		});
	}
}

void CastHeavyBlade::onCleanup()
{
}

bool CastHeavyBlade::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<HeavyBlade>([&](HeavyBlade* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastHeavyBlade::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
