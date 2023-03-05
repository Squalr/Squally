#include "CastUnholyBlade.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/UnholyBlade/UnholyBlade.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastUnholyBlade* CastUnholyBlade::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastUnholyBlade* instance = new CastUnholyBlade(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastUnholyBlade::CastUnholyBlade(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_SwordGlowYellow, priority, AbilityType::Shadow, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastUnholyBlade::~CastUnholyBlade()
{
}

void CastUnholyBlade::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastUnholyBlade::cloneInternal()
{
	return CastUnholyBlade::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastUnholyBlade::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_UnholyBlade::create();
}

std::string CastUnholyBlade::getAttackAnimation()
{
	return "AttackCast";
}

void CastUnholyBlade::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(UnholyBlade::create(owner, next));
		});
	}
}

void CastUnholyBlade::onCleanup()
{
}

bool CastUnholyBlade::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	int uncastableCount = 0;

	for (auto next : otherTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			uncastableCount++;
			continue;
		}

		next->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->getBuff<UnholyBlade>([&](UnholyBlade* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastUnholyBlade::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	float utility = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 1.0f : 0.0f;

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<UnholyBlade>([&](UnholyBlade* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
