#include "CastManaDrain.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/ManaDrain/ManaDrain.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastManaDrain* CastManaDrain::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastManaDrain* instance = new CastManaDrain(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastManaDrain::CastManaDrain(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Debuff, UIResources::Menus_Icons_ManaSkull, priority, AbilityType::Shadow, 0, 0, 5, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);

	this->addChild(this->castSound);
}

CastManaDrain::~CastManaDrain()
{
}

void CastManaDrain::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastManaDrain::cloneInternal()
{
	return CastManaDrain::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastManaDrain::getString()
{
	return Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_ManaDrain::create();
}

std::string CastManaDrain::getAttackAnimation()
{
	return "AttackCast";
}

void CastManaDrain::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(ManaDrain::create(owner, next));
		});
	}
}

void CastManaDrain::onCleanup()
{
}

bool CastManaDrain::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
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
			entityBuffBehavior->getBuff<ManaDrain>([&](ManaDrain* debuff)
			{
				uncastableCount++;
			});
		});
	}

	return uncastableCount != int(otherTeam.size());
}

float CastManaDrain::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool isAlive = target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true);
	bool isPacifist = target->getRuntimeStateOrDefaultBool(StateKeys::IsPacifist, true);
	float mana = float(target->getRuntimeStateOrDefaultInt(StateKeys::Mana, 0));
	float maxMana = float(target->getRuntimeStateOrDefaultInt(StateKeys::MaxMana, 0));
	float utility = (isAlive && !isPacifist) ? 1.0f : (mana / (maxMana <= 0.0f ? 1.0f : maxMana));

	target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<ManaDrain>([&](ManaDrain* debuff)
		{
			utility = 0.0f;
		});
	});
	
	return utility;
}
