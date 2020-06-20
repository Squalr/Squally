#include "DoubleSlash.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DoubleSlash* DoubleSlash::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority, float weaveDelay)
{
	DoubleSlash* instance = new DoubleSlash(damageMin, damageMax, attackDuration, recoverDuration, priority, weaveDelay);

	instance->autorelease();

	return instance;
}

DoubleSlash::DoubleSlash(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority, float weaveDelay)
	: super(
		AttackType::Damage,
		UIResources::Menus_Icons_SwordsCrossed,
		priority,
		AbilityType::Physical,
		damageMin,
		damageMax,
		0,
		attackDuration,
		recoverDuration,
		true
	)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Physical_Swings_SwingBlade1);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Physical_Impact_HitSoft1);
	this->weaveDelay = weaveDelay;

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

DoubleSlash::~DoubleSlash()
{
}

PlatformerAttack* DoubleSlash::cloneInternal()
{
	return DoubleSlash::create(this->getBaseDamageMin(), this->getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* DoubleSlash::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string DoubleSlash::getAttackAnimation()
{
	return "Attack";
}

void DoubleSlash::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->slashSound->play(false, this->attackDuration / 2.0f);
}

void DoubleSlash::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (int index = 0; index < int(targets.size()); index++)
	{
		this->runAction(Sequence::create(
			DelayTime::create(float(index) * this->weaveDelay),
			CallFunc::create([=]()
			{
				this->doDamageOrHealing(owner, targets[index]);
			}),
			nullptr
		));
	}
}

void DoubleSlash::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->hitSound->play();
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage(), this->abilityType));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
