#include "CastLifeSteal.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float CastLifeSteal::DamageMultiplier = 1.25f;

CastLifeSteal* CastLifeSteal::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
{
	CastLifeSteal* instance = new CastLifeSteal(damageMin, damageMax, attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastLifeSteal::CastLifeSteal(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Damage,
		UIResources::Menus_Icons_WandCrystal,
		priority,
		AbilityType::Shadow,
		damageMin,
		damageMax,
		6,
		attackDuration,
		recoverDuration
	)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Physical_Swings_SwingBlade2);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Physical_Impact_HitSoft1);

	this->setDamageMultiplier(CastLifeSteal::DamageMultiplier);

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

CastLifeSteal::~CastLifeSteal()
{
}

PlatformerAttack* CastLifeSteal::cloneInternal()
{
	return CastLifeSteal::create(this->getBaseDamageMin(), this->getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastLifeSteal::getString()
{
	return Strings::Platformer_Combat_Attacks_LifeSteal::create();
}

LocalizedString* CastLifeSteal::getDescription()
{
	return Strings::Platformer_Combat_Attacks_LifeStealDescription::create()
		->setStringReplacementVariables({ ConstantString::create(std::to_string(int(CastLifeSteal::DamageMultiplier * 100.0f))), Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Grim::create() });
}

std::string CastLifeSteal::getAttackAnimation()
{
	return "Attack";
}

void CastLifeSteal::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->slashSound->play(false, this->attackDuration / 2.0f);
}

void CastLifeSteal::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (PlatformerEntity* next : targets)
	{
		this->doDamageOrHealing(owner, next);
	}
}

void CastLifeSteal::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->hitSound->play();

	int damage = this->getRandomDamage();
	int healing = damage;

	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, damage, this->abilityType));
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(owner, owner, healing, this->abilityType));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
