#include "CastResurrection.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/Resurrection/Resurrection.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float CastResurrection::HealPercentage = 0.5f;

CastResurrection* CastResurrection::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastResurrection* instance = new CastResurrection(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastResurrection::CastResurrection(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Resurrection, UIResources::Menus_Icons_Ankh, priority, AbilityType::Holy, 0, 0, 8, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Notifications_Reveal1);

	this->addChild(this->castSound);
}

CastResurrection::~CastResurrection()
{
}

void CastResurrection::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastResurrection::cloneInternal()
{
	return CastResurrection::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastResurrection::getString()
{
	return Strings::Platformer_Combat_Attacks_Resurrect::create();
}

LocalizedString* CastResurrection::getDescription()
{
	return Strings::Platformer_Combat_Attacks_ResurrectDescription::create()
		->setStringReplacementVariables(ConstantString::create(std::to_string(int(CastResurrection::HealPercentage * 100.0f))));
}

std::string CastResurrection::getAttackAnimation()
{
	return "AttackCast";
}

void CastResurrection::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Resurrection::create(owner, next), false);
		});

		next->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* entityHealthBehavior)
		{
			entityHealthBehavior->setHealth(int(float(entityHealthBehavior->getMaxHealth() * CastResurrection::HealPercentage)), false);
		});
	}
}

void CastResurrection::onCleanup()
{
}

bool CastResurrection::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	for (auto next : sameTeam)
	{
		if (!next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			return true;
		}
	}
	
	return false;
}

float CastResurrection::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) ? 0.0f : 1.0f;
}
