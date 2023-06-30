#include "CastThorns.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Thorns/Thorns.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastThorns* CastThorns::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastThorns* instance = new CastThorns(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastThorns::CastThorns(float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Defensive,
		UIResources::Menus_Icons_ShieldThorned,
		priority,
		AbilityType::Nature,
		0,
		0,
		8,
		attackDuration,
		recoverDuration,
		TargetingType::Self
	)
{
	this->defendSound = WorldSound::create(SoundResources::Platformer_Defense_Rebound2);

	this->addChild(this->defendSound);
}

CastThorns::~CastThorns()
{
}

PlatformerAttack* CastThorns::cloneInternal()
{
	return CastThorns::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastThorns::getString()
{
	return Strings::Platformer_Combat_Defensives_Thorns::create();
}

LocalizedString* CastThorns::getDescription()
{
	return Strings::Platformer_Combat_Defensives_ThornsDescription::create();
}

std::string CastThorns::getAttackAnimation()
{
	return "AttackCast";
}

void CastThorns::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	this->defendSound->play(false, 0.0f);

	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Thorns::create(owner));
	});
}
