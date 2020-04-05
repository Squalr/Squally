#include "CastReflect.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Reflect/Reflect.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastReflect* CastReflect::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastReflect* instance = new CastReflect(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastReflect::CastReflect(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Buff, UIResources::Menus_Icons_Shield, priority, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal5);

	this->addChild(this->castSound);
}

CastReflect::~CastReflect()
{
}

void CastReflect::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastReflect::cloneInternal()
{
	return CastReflect::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastReflect::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Reflect_Reflect::create();
}

std::string CastReflect::getAttackAnimation()
{
	return "AttackCast";
}

void CastReflect::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	owner->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Reflect::create(owner, target));
	});
}

void CastReflect::onCleanup()
{
}

bool CastReflect::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Reflect>([&](Reflect* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}
