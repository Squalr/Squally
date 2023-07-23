#include "CastCalcify.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/CombatUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Calcify/Calcify.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastCalcify* CastCalcify::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastCalcify* instance = new CastCalcify(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastCalcify::CastCalcify(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_Bone, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastCalcify::~CastCalcify()
{
}

void CastCalcify::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastCalcify::cloneInternal()
{
	return CastCalcify::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastCalcify::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Calcify_Calcify::create();
}

std::string CastCalcify::getAttackAnimation()
{
	return "AttackCast";
}

void CastCalcify::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Calcify::create(owner, next));
		});
	}
}

void CastCalcify::onCleanup()
{
}

bool CastCalcify::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Calcify>([&](Calcify* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastCalcify::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
