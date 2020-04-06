#include "CastBlind.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Blind/Blind.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastBlind* CastBlind::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastBlind* instance = new CastBlind(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastBlind::CastBlind(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Debuff, UIResources::Menus_Icons_Clock, priority, 0, 0, 2, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastBlind::~CastBlind()
{
}

void CastBlind::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastBlind::cloneInternal()
{
	return CastBlind::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastBlind::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_Blind_Blind::create();
}

std::string CastBlind::getAttackAnimation()
{
	return "AttackCast";
}

void CastBlind::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	target->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Blind::create(owner, target));
	});
}

void CastBlind::onCleanup()
{
}

bool CastBlind::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Blind>([&](Blind* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}
