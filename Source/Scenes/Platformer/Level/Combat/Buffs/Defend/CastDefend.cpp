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

CastDefend* CastDefend::create(Priority priority)
{
	CastDefend* instance = new CastDefend(priority);

	instance->autorelease();

	return instance;
}

CastDefend::CastDefend(Priority priority)
	: super(
		AttackType::Buff,
		UIResources::Menus_Icons_Shield,
		priority,
		AbilityType::Physical,
		0,
		0,
		0,
		0.0f,
		0.0f,
		TargetingType::Self
	)
{
	this->defendSound = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);

	this->addChild(this->defendSound);
}

CastDefend::~CastDefend()
{
}

PlatformerAttack* CastDefend::cloneInternal()
{
	return CastDefend::create(this->priority);
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

void CastDefend::onAttackStaged()
{
	super::onAttackStaged();
	
	this->defendSound->play(false, this->attackDuration);

	this->execute(this->owner, {}, nullptr, nullptr);
}

void CastDefend::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Defend::create(owner));
	});
}
