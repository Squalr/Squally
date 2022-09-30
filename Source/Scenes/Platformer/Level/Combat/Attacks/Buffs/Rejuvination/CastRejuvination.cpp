#include "CastRejuvination.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Rejuvination/Rejuvination.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastRejuvination* CastRejuvination::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastRejuvination* instance = new CastRejuvination(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastRejuvination::CastRejuvination(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_MoonShine, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Team)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastRejuvination::~CastRejuvination()
{
}

void CastRejuvination::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastRejuvination::cloneInternal()
{
	return CastRejuvination::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastRejuvination::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_Rejuvination_Rejuvination::create();
}

std::string CastRejuvination::getAttackAnimation()
{
	return "AttackCast";
}

void CastRejuvination::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());
	
	for (auto next : targets)
	{
		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(Rejuvination::create(owner, next));
		});
	}
}

void CastRejuvination::onCleanup()
{
}

bool CastRejuvination::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (TimelineEntry* next : timeline->getEntries())
		{
			if (dynamic_cast<CastRejuvination*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<Rejuvination>([&](Rejuvination*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastRejuvination::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
