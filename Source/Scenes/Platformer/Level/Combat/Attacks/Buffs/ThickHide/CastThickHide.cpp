#include "CastThickHide.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ThickHide/ThickHide.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastThickHide* CastThickHide::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastThickHide* instance = new CastThickHide(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastThickHide::CastThickHide(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_Piggy, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastThickHide::~CastThickHide()
{
}

void CastThickHide::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastThickHide::cloneInternal()
{
	return CastThickHide::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastThickHide::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_ThickHide_ThickHide::create();
}

std::string CastThickHide::getAttackAnimation()
{
	return "AttackCast";
}

void CastThickHide::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(ThickHide::create(owner, next));
		});
	}
}

void CastThickHide::onCleanup()
{
}

bool CastThickHide::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<ThickHide>([&](ThickHide* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastThickHide::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
