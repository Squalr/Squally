#include "CastCondensation.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/Spells/Condensation/Condensation.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const int CastCondensation::ManaGain = 12;

CastCondensation* CastCondensation::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastCondensation* instance = new CastCondensation(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastCondensation::CastCondensation(float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Buff,
		UIResources::Menus_Icons_Bubbles,
		priority,
		AbilityType::Water,
		0,
		0,
		0,
		attackDuration,
		recoverDuration,
		TargetingType::Self
	)
{
	this->bubbleSound = WorldSound::create(SoundResources::Platformer_Spells_Bubbles3);

	this->addChild(this->bubbleSound);
}

CastCondensation::~CastCondensation()
{
}

PlatformerAttack* CastCondensation::cloneInternal()
{
	return CastCondensation::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastCondensation::getString()
{
	return Strings::Platformer_Combat_Attacks_Condensation::create();
}

LocalizedString* CastCondensation::getDescription()
{
	return Strings::Platformer_Combat_Attacks_CondensationDescription::create()
		->setStringReplacementVariables(ConstantString::create(std::to_string(int(CastCondensation::ManaGain))));
}

std::string CastCondensation::getAttackAnimation()
{
	return "AttackCast";
}

void CastCondensation::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->bubbleSound->play(false, this->attackDuration);
}

void CastCondensation::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (auto next : targets)
	{
		CombatEvents::TriggerManaRestore(CombatEvents::ManaRestoreOrDrainArgs(next, this->owner, CastCondensation::ManaGain, this->abilityType));

		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Condensation::create(owner, next));
		});
	}
}
