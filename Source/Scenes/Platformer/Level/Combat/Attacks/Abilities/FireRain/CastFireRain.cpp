#include "CastFireRain.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/FireRain/FireRain.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastFireRain* CastFireRain::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastFireRain* instance = new CastFireRain(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastFireRain::CastFireRain(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_FireBolts, priority, AbilityType::Fire, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Multi)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastFireRain::~CastFireRain()
{
}

void CastFireRain::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastFireRain::cloneInternal()
{
	return CastFireRain::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastFireRain::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_FireRain_FireRain::create();
}

std::string CastFireRain::getAttackAnimation()
{
	return "AttackCast";
}

void CastFireRain::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	ObjectEvents::QueryObject<CinematicMarker>([=](CinematicMarker* marker)
	{
		FireRain* arrowRain = FireRain::create(owner, nullptr);

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			marker,
			arrowRain,
			SpawnMethod::Above,
			PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));

		// Place it quasi off-screen
		arrowRain->setPosition(arrowRain->getPosition() + Vec2(0.0f, 512.0f));
	},
	PlatformerAttack::TagArenaBottom,
	[=]()
	{
		// TOP CENTER ARENA MARKER NOT FOUND!
		FireRain* arrowRain = FireRain::create(owner, nullptr);

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			this,
			arrowRain,
			SpawnMethod::Above,
			PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));
		
		// Fall back by spawning the arrow rain in a quasi reasonable spot.
		arrowRain->setPosition(arrowRain->getPosition() + Vec2(-256.0f, 256.0f));
	});
}

void CastFireRain::onCleanup()
{
}

bool CastFireRain::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (TimelineEntry* next : timeline->getEntries())
		{
			if (dynamic_cast<CastFireRain*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<FireRain>([&](FireRain*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastFireRain::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
