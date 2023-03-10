#include "CastMelt.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Melt/Melt.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastMelt* CastMelt::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastMelt* instance = new CastMelt(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastMelt::CastMelt(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_FlamingScroll, priority, AbilityType::Fire, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastMelt::~CastMelt()
{
}

void CastMelt::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastMelt::cloneInternal()
{
	return CastMelt::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastMelt::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_Melt_Melt::create();
}

std::string CastMelt::getAttackAnimation()
{
	return "AttackCast";
}

void CastMelt::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Melt::create(owner, next));
		});
	}
}

void CastMelt::onCleanup()
{
}

bool CastMelt::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Melt>([&](Melt* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastMelt::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
