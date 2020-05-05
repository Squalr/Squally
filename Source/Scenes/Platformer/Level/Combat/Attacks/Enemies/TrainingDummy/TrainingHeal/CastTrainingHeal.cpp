#include "CastTrainingHeal.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/TrainingDummy/TrainingHeal/TrainingHeal.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastTrainingHeal* CastTrainingHeal::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastTrainingHeal* instance = new CastTrainingHeal(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastTrainingHeal::CastTrainingHeal(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Healing, UIResources::Menus_Icons_Heal, priority, 0, 0, 1, attackDuration, recoverDuration)
{
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Heal1);
	
	this->addChild(this->healSound);
}

CastTrainingHeal::~CastTrainingHeal()
{
}

void CastTrainingHeal::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f));
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

void CastTrainingHeal::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->healSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	const int Ticks = 7;

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(TrainingHeal::create(owner, next, Ticks));
		});
	}
}

void CastTrainingHeal::onCleanup()
{
}
