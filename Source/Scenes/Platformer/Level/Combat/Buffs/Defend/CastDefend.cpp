#include "CastDefend.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Defend/Defend.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastDefend* CastDefend::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastDefend* instance = new CastDefend(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastDefend::CastDefend(float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Defensive,
		UIResources::Menus_Icons_Shield,
		priority,
		AbilityType::Physical,
		0,
		0,
		0,
		attackDuration,
		recoverDuration,
		TargetingType::Self
	)
{
	this->defendSound = WorldSound::create(SoundResources::Platformer_Defense_Rebound2);

	this->addChild(this->defendSound);
}

CastDefend::~CastDefend()
{
}

PlatformerAttack* CastDefend::cloneInternal()
{
	return CastDefend::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastDefend::getString()
{
	return Strings::Platformer_Combat_Defensives_Defend::create();
}

LocalizedString* CastDefend::getDescription()
{
	return Strings::Platformer_Combat_Defensives_DefendDescription::create();
}

std::string CastDefend::getAttackAnimation()
{
	return "AttackCast";
}

void CastDefend::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	this->defendSound->play(false, 0.0f);

	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Defend::create(owner, false));
	});
}
