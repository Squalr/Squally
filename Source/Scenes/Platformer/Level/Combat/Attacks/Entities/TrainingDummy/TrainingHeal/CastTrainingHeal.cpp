#include "CastTrainingHeal.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/TrainingDummy/TrainingHeal/TrainingHeal.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastTrainingHeal* CastTrainingHeal::create(float attackDuration, float recoverDuration, float priority)
{
	CastTrainingHeal* instance = new CastTrainingHeal(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastTrainingHeal::CastTrainingHeal(float attackDuration, float recoverDuration, float priority) : super(AttackType::Buff, UIResources::Menus_Icons_Health, priority, 0, 0, 1, attackDuration, recoverDuration)
{
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);
	this->healSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal1);

	this->spellAura->setOpacity(0);

	this->addChild(this->spellAura);
	this->addChild(this->healSound);
}

CastTrainingHeal::~CastTrainingHeal()
{
}

PlatformerAttack* CastTrainingHeal::cloneInternal()
{
	return CastTrainingHeal::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastTrainingHeal::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string CastTrainingHeal::getAttackAnimation()
{
	return "AttackCast";
}

void CastTrainingHeal::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");
	
	const int Ticks = 5;

	owner->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(TrainingHeal::create(owner, target, Ticks));
	});
}

void CastTrainingHeal::onCleanup()
{
}
