#include "CastStoneSkin.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/StoneSkin/StoneSkin.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastStoneSkin* CastStoneSkin::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastStoneSkin* instance = new CastStoneSkin(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastStoneSkin::CastStoneSkin(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_ShieldBroken, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastStoneSkin::~CastStoneSkin()
{
}

void CastStoneSkin::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastStoneSkin::cloneInternal()
{
	return CastStoneSkin::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastStoneSkin::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_StoneSkin_StoneSkin::create();
}

std::string CastStoneSkin::getAttackAnimation()
{
	return "AttackCast";
}

void CastStoneSkin::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");
	
	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(StoneSkin::create(owner, next));
		});
	}
}

void CastStoneSkin::onCleanup()
{
}

bool CastStoneSkin::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<StoneSkin>([&](StoneSkin* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastStoneSkin::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
