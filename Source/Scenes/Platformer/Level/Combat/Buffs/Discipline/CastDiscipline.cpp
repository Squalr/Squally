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

CastDiscipline* CastDiscipline::create(Priority priority)
{
	CastDiscipline* instance = new CastDiscipline(priority);

	instance->autorelease();

	return instance;
}

CastDiscipline::CastDiscipline(Priority priority)
	: super(
		AttackType::Buff,
		UIResources::Menus_Icons_HeartPurple,
		priority,
		AbilityType::Arcane,
		0,
		0,
		8,
		0.0f,
		0.0f,
		TargetingType::Self
	)
{
	this->disciplineSound = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);

	this->addChild(this->disciplineSound);
}

CastDiscipline::~CastDiscipline()
{
}

PlatformerAttack* CastDiscipline::cloneInternal()
{
	return CastDiscipline::create(this->priority);
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

void CastDiscipline::onAttackStaged()
{
	super::onAttackStaged();
	
	this->disciplineSound->play(false, this->attackDuration);

	this->execute(this->owner, {}, nullptr, nullptr);
}

void CastDiscipline::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Discipline::create(owner));
	});
}
