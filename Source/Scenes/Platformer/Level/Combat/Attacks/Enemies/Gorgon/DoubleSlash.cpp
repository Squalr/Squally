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

DoubleSlash* DoubleSlash::create(float attackDuration, float recoverDuration, Priority priority)
{
	DoubleSlash* instance = new DoubleSlash(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

DoubleSlash::DoubleSlash(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Damage, UIResources::Menus_Icons_SwordSlash, priority, 3, 5, 0, attackDuration, recoverDuration)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Swings_SwingBlade1);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Impact_HitSoft1);

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

DoubleSlash::~DoubleSlash()
{
}

PlatformerAttack* DoubleSlash::cloneInternal()
{
	return DoubleSlash::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
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
			DelayTime::create(float(index) * 1.0f),
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
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
