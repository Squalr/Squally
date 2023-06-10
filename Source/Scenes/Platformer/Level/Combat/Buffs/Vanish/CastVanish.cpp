#include "CastVanish.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Vanish/Vanish.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastVanish* CastVanish::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastVanish* instance = new CastVanish(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastVanish::CastVanish(float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Defensive,
		UIResources::Menus_Icons_BookSpellsDark,
		priority,
		AbilityType::Shadow,
		0,
		0,
		8,
		attackDuration,
		recoverDuration,
		TargetingType::Self
	)
{
	this->sfx = WorldSound::create(SoundResources::Platformer_Spells_Curse1);

	this->addChild(this->sfx);
}

CastVanish::~CastVanish()
{
}

PlatformerAttack* CastVanish::cloneInternal()
{
	return CastVanish::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastVanish::getString()
{
	return Strings::Platformer_Combat_Defensives_Vanish::create();
}

LocalizedString* CastVanish::getDescription()
{
	return Strings::Platformer_Combat_Defensives_VanishDescription::create();
}

std::string CastVanish::getAttackAnimation()
{
	return "AttackCast";
}

void CastVanish::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	this->sfx->play(false, this->attackDuration);

	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Vanish::create(owner));
	});
}
