#include "CastFortitude.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Fortitude/Fortitude.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastFortitude* CastFortitude::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastFortitude* instance = new CastFortitude(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastFortitude::CastFortitude(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Buff, UIResources::Menus_Icons_Shield, priority, 0, 0, 4, attackDuration, recoverDuration)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastFortitude::~CastFortitude()
{
}

void CastFortitude::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastFortitude::cloneInternal()
{
	return CastFortitude::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastFortitude::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Fortitude_Fortitude::create();
}

std::string CastFortitude::getAttackAnimation()
{
	return "AttackCast";
}

void CastFortitude::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	for (auto next : targets)
	{
		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Fortitude::create(owner, next));
		});
	}
}

void CastFortitude::onCleanup()
{
}

bool CastFortitude::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool hasBuff = false;

	caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->getBuff<Fortitude>([&](Fortitude* haste)
		{
			hasBuff = true;
		});
	});

	return !hasBuff;
}
