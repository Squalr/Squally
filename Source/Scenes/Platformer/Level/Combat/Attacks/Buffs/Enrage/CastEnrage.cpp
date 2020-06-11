#include "CastEnrage.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Enrage/Enrage.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastEnrage* CastEnrage::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastEnrage* instance = new CastEnrage(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastEnrage::CastEnrage(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_Clock, priority, 0, 0, 2, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastEnrage::~CastEnrage()
{
}

void CastEnrage::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastEnrage::cloneInternal()
{
	return CastEnrage::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastEnrage::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Enrage_Enrage::create();
}

std::string CastEnrage::getAttackAnimation()
{
	return "AttackCast";
}

void CastEnrage::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Enrage::create(owner, next));
		});
	}
}

void CastEnrage::onCleanup()
{
}

bool CastEnrage::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Enrage>([&](Enrage* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastEnrage::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
