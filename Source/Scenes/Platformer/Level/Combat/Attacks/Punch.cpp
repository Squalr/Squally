#include "Punch.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/Sound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

Punch* Punch::create(float attackDuration, float recoverDuration, Priority priority)
{
	Punch* instance = new Punch(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

Punch::Punch(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Damage, UIResources::Menus_Icons_Punch, priority, -3, -5, 0, attackDuration, recoverDuration)
{
	this->punchSound = Sound::create(SoundResources::Platformer_Combat_Attacks_Physical_Punches_Punch7);

	this->addChild(this->punchSound);
}

Punch::~Punch()
{
}

PlatformerAttack* Punch::cloneInternal()
{
	return Punch::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* Punch::getString()
{
	return Strings::Platformer_Combat_Attacks_Punch::create();
}

std::string Punch::getAttackAnimation()
{
	return "AttackPunch";
}

void Punch::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();

	this->punchSound->play(false, this->attackDuration / 2.0f);
}

void Punch::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (auto next : targets)
	{
		this->doDamageOrHealing(owner, next);
	}
}

void Punch::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
