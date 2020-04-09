#include "CastStoneSkinHaste.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Haste/Haste.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/StoneSkin/StoneSkin.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastStoneSkinHaste* CastStoneSkinHaste::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastStoneSkinHaste* instance = new CastStoneSkinHaste(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastStoneSkinHaste::CastStoneSkinHaste(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Buff, UIResources::Menus_Icons_Clock, priority, 0, 0, 12, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal5);

	this->addChild(this->castSound);
}

CastStoneSkinHaste::~CastStoneSkinHaste()
{
}

void CastStoneSkinHaste::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastStoneSkinHaste::cloneInternal()
{
	return CastStoneSkinHaste::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastStoneSkinHaste::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Haste_Haste::create();
}

std::string CastStoneSkinHaste::getAttackAnimation()
{
	return "AttackCast";
}

void CastStoneSkinHaste::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
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
			entityBuffBehavior->applyBuff(StoneSkin::create(owner, next));
		});
	}
}

void CastStoneSkinHaste::onCleanup()
{
}

bool CastStoneSkinHaste::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Haste>([&](Haste* haste)
		{
			hasBuff = true;
		});

		entityBuffBehavior->getBuff<StoneSkin>([&](StoneSkin* stoneSkin)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastStoneSkinHaste::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
