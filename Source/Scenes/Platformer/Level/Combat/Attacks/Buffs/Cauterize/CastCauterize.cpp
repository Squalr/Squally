#include "CastCauterize.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Cauterize/Cauterize.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastCauterize* CastCauterize::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastCauterize* instance = new CastCauterize(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastCauterize::CastCauterize(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_WandGlowYellow, priority, AbilityType::Nature, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Self)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastCauterize::~CastCauterize()
{
}

void CastCauterize::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastCauterize::cloneInternal()
{
	return CastCauterize::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastCauterize::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_Cauterize_Cauterize::create();
}

std::string CastCauterize::getAttackAnimation()
{
	return "AttackCast";
}

void CastCauterize::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());
	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Cauterize::create(owner, owner));
	});
}

void CastCauterize::onCleanup()
{
}

bool CastCauterize::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (TimelineEntry* next : timeline->getEntries())
		{
			if (dynamic_cast<CastCauterize*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<Cauterize>([&](Cauterize*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastCauterize::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
