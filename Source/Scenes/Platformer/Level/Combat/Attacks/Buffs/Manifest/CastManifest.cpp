#include "CastManifest.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Manifest/Manifest.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastManifest* CastManifest::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastManifest* instance = new CastManifest(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastManifest::CastManifest(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_SwordGlowRed, priority, AbilityType::Physical, 0, 0, 3, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastManifest::~CastManifest()
{
}

void CastManifest::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastManifest::cloneInternal()
{
	return CastManifest::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastManifest::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Manifest_Manifest::create();
}

std::string CastManifest::getAttackAnimation()
{
	return "AttackCast";
}

void CastManifest::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Manifest::create(owner, next));
		});
	}
}

void CastManifest::onCleanup()
{
}

bool CastManifest::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Manifest>([&](Manifest* buff)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastManifest::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
