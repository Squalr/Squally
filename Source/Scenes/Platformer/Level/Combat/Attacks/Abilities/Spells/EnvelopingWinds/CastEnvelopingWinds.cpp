#include "CastEnvelopingWinds.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/EnvelopingWinds/EnvelopingWinds.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastEnvelopingWinds* CastEnvelopingWinds::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastEnvelopingWinds* instance = new CastEnvelopingWinds(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastEnvelopingWinds::CastEnvelopingWinds(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_Fog, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Multi)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastEnvelopingWinds::~CastEnvelopingWinds()
{
}

void CastEnvelopingWinds::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastEnvelopingWinds::cloneInternal()
{
	return CastEnvelopingWinds::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastEnvelopingWinds::getString()
{
	return Strings::Platformer_Combat_Attacks_EnvelopingWinds::create();
}

std::string CastEnvelopingWinds::getAttackAnimation()
{
	return "AttackCast";
}

void CastEnvelopingWinds::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	ObjectEvents::QueryObject<CinematicMarker>(this, [=](CinematicMarker* marker)
	{
		EnvelopingWinds* envelopingWinds = EnvelopingWinds::create(owner, nullptr);

		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
			marker,
			envelopingWinds,
			ObjectEvents::SpawnMethod::Above,
			ObjectEvents::PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));

		// We spawned the wind to the arena center, but actually we want to snap the X back to the owner.
		envelopingWinds->setPosition(Vec2(owner->getPositionX() - 32.0f, envelopingWinds->getPositionY() + 256.0f));
	},
	[=]()
	{
		// TOP CENTER ARENA MARKER NOT FOUND!
		EnvelopingWinds* envelopingWinds = EnvelopingWinds::create(owner, nullptr);

		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
			this,
			envelopingWinds,
			ObjectEvents::SpawnMethod::Above,
			ObjectEvents::PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));
		
		// Fall back by spawning in a quasi reasonable spot.
		envelopingWinds->setPosition(envelopingWinds->getPosition() + Vec2(-32.0f, 256.0f));
	}, PlatformerAttack::TagArenaCenter);
}

void CastEnvelopingWinds::onCleanup()
{
}

bool CastEnvelopingWinds::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (auto next : timeline->getEntries())
		{
			if (dynamic_cast<CastEnvelopingWinds*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<EnvelopingWinds>(this, [&](EnvelopingWinds*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastEnvelopingWinds::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
