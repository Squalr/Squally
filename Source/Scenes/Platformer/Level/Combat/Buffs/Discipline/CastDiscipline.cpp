#include "CastDiscipline.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Discipline/Discipline.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastDiscipline* CastDiscipline::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastDiscipline* instance = new CastDiscipline(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastDiscipline::CastDiscipline(float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Defensive,
		UIResources::Menus_Icons_HeartPurple,
		priority,
		AbilityType::Arcane,
		0,
		0,
		5,
		attackDuration,
		recoverDuration,
		TargetingType::Self
	)
{
	this->disciplineSound = WorldSound::create(SoundResources::Platformer_Defense_Rebound2);

	this->addChild(this->disciplineSound);
}

CastDiscipline::~CastDiscipline()
{
}

PlatformerAttack* CastDiscipline::cloneInternal()
{
	return CastDiscipline::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastDiscipline::getString()
{
	return Strings::Platformer_Combat_Defensives_Discipline::create();
}

LocalizedString* CastDiscipline::getDescription()
{
	return Strings::Platformer_Combat_Defensives_DisciplineDescription::create();
}

std::string CastDiscipline::getAttackAnimation()
{
	return "AttackCast";
}

void CastDiscipline::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	this->disciplineSound->play(false, 0.0f);

	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Discipline::create(owner));
	});
}
