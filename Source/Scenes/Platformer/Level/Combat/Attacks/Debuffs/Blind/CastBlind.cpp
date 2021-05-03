#include "CastBlind.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
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

CastBlind::CastBlind(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_EyeStrain, priority, AbilityType::Physical, 0, 0, 3, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

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

void CastBlind::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Blind::create(owner, next));
		});
	}
}

void CastBlind::onCleanup()
{
}

bool CastBlind::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Blind>([&](Blind* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastBlind::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
