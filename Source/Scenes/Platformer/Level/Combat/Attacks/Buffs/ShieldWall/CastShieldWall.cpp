#include "CastShieldWall.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ShieldWall/ShieldWall.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastShieldWall* CastShieldWall::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastShieldWall* instance = new CastShieldWall(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastShieldWall::CastShieldWall(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_ShieldGlowOrange, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastShieldWall::~CastShieldWall()
{
}

void CastShieldWall::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastShieldWall::cloneInternal()
{
	return CastShieldWall::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastShieldWall::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_ShieldWall_ShieldWall::create();
}

std::string CastShieldWall::getAttackAnimation()
{
	return "AttackCast";
}

void CastShieldWall::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(ShieldWall::create(owner, next));
		});
	}
}

void CastShieldWall::onCleanup()
{
}

bool CastShieldWall::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<ShieldWall>([&](ShieldWall* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastShieldWall::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
