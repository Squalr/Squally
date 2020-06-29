#include "CastInversion.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Inversion/Inversion.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastInversion* CastInversion::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastInversion* instance = new CastInversion(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastInversion::CastInversion(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_YinYang, priority, AbilityType::Shadow, 0, 0, 8, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastInversion::~CastInversion()
{
}

void CastInversion::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastInversion::cloneInternal()
{
	return CastInversion::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastInversion::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Inversion_Inversion::create();
}

std::string CastInversion::getAttackAnimation()
{
	return "AttackCast";
}

void CastInversion::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());
	
	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Inversion::create(owner, next));
		});
	}
}

void CastInversion::onCleanup()
{
}

bool CastInversion::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Inversion>([&](Inversion* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastInversion::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
