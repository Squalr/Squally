#include "CastLesserStrength.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/LesserStrength/LesserStrength.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastLesserStrength* CastLesserStrength::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastLesserStrength* instance = new CastLesserStrength(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastLesserStrength::CastLesserStrength(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Buff, UIResources::Menus_Icons_Clock, priority, 0, 0, 2, attackDuration, recoverDuration)
{
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->castSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal5);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellAura);
	this->addChild(this->castSound);
}

CastLesserStrength::~CastLesserStrength()
{
}

void CastLesserStrength::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f));
}

PlatformerAttack* CastLesserStrength::cloneInternal()
{
	return CastLesserStrength::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastLesserStrength::getString()
{
	return Strings::Menus_Hacking_Abilities_LesserStrength_LesserStrength::create();
}

std::string CastLesserStrength::getAttackAnimation()
{
	return "AttackCast";
}

void CastLesserStrength::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	owner->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(LesserStrength::create(owner, target));
	});

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));
}

void CastLesserStrength::onCleanup()
{
}

bool CastLesserStrength::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasSpeedBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<LesserStrength>([&](LesserStrength* haste)
		{
			hasSpeedBuff = true;
		});
	});

	return !hasSpeedBuff;
}
