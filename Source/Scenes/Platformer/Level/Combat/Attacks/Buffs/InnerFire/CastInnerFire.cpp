#include "CastInnerFire.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/InnerFire/InnerFire.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastInnerFire* CastInnerFire::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastInnerFire* instance = new CastInnerFire(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastInnerFire::CastInnerFire(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_MoonShine, priority, AbilityType::Nature, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Self)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastInnerFire::~CastInnerFire()
{
}

void CastInnerFire::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastInnerFire::cloneInternal()
{
	return CastInnerFire::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastInnerFire::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_InnerFire_InnerFire::create();
}

std::string CastInnerFire::getAttackAnimation()
{
	return "AttackCast";
}

void CastInnerFire::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());
	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(InnerFire::create(owner, owner));
	});
}

void CastInnerFire::onCleanup()
{
}

bool CastInnerFire::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (TimelineEntry* next : timeline->getEntries())
		{
			if (dynamic_cast<CastInnerFire*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<InnerFire>([&](InnerFire*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastInnerFire::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
