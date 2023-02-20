#include "CastEnchantedBlade.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/EnchantedBlade/EnchantedBlade.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastEnchantedBlade* CastEnchantedBlade::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastEnchantedBlade* instance = new CastEnchantedBlade(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastEnchantedBlade::CastEnchantedBlade(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_ShieldGlowBlue, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastEnchantedBlade::~CastEnchantedBlade()
{
}

void CastEnchantedBlade::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastEnchantedBlade::cloneInternal()
{
	return CastEnchantedBlade::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastEnchantedBlade::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_EnchantedBlade_EnchantedBlade::create();
}

std::string CastEnchantedBlade::getAttackAnimation()
{
	return "AttackCast";
}

void CastEnchantedBlade::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(EnchantedBlade::create(owner, next));
		});
	}
}

void CastEnchantedBlade::onCleanup()
{
}

bool CastEnchantedBlade::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<EnchantedBlade>([&](EnchantedBlade* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastEnchantedBlade::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
