#include "CastHaste.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Haste/Haste.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastHaste* CastHaste::create(float attackDuration, float recoverDuration, float priority)
{
	CastHaste* instance = new CastHaste(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastHaste::CastHaste(float attackDuration, float recoverDuration, float priority) : super(AttackType::Healing, UIResources::Menus_Icons_Health, priority, 0, 0, 2, attackDuration, recoverDuration)
{
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);
	this->healSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal1);

	this->spellAura->setOpacity(0);

	this->addChild(this->spellAura);
	this->addChild(this->healSound);
}

CastHaste::~CastHaste()
{
}

void CastHaste::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f));
}

PlatformerAttack* CastHaste::cloneInternal()
{
	return CastHaste::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastHaste::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string CastHaste::getAttackAnimation()
{
	return "AttackCast";
}

void CastHaste::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	this->healSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");
	
	const int Ticks = 7;

	owner->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Haste::create(owner, target, Ticks));
	});

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));
}

void CastHaste::onCleanup()
{
}
