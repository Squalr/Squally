#include "CastEnchantment.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Enchantment/Enchantment.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastEnchantment* CastEnchantment::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastEnchantment* instance = new CastEnchantment(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastEnchantment::CastEnchantment(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Buff, UIResources::Menus_Icons_WandSkeleton, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastEnchantment::~CastEnchantment()
{
}

void CastEnchantment::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastEnchantment::cloneInternal()
{
	return CastEnchantment::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastEnchantment::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Enchantment_Enchantment::create();
}

std::string CastEnchantment::getAttackAnimation()
{
	return "AttackCast";
}

void CastEnchantment::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (PlatformerEntity* next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Enchantment::create(owner, next));
		});
	}
}

void CastEnchantment::onCleanup()
{
}

bool CastEnchantment::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Enchantment>([&](Enchantment* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}

float CastEnchantment::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	// Prioritize self-cast
	return target == this->owner ? 1.0f : 0.0f;
}
