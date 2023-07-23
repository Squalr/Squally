#include "CastArrowVolley.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/ArrowVolley/ArrowVolley.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastArrowVolley* CastArrowVolley::create(float attackDuration, float recoverDuration, Priority priority, std::string arrowResource)
{
	CastArrowVolley* instance = new CastArrowVolley(attackDuration, recoverDuration, priority, arrowResource);

	instance->autorelease();

	return instance;
}

CastArrowVolley::CastArrowVolley(float attackDuration, float recoverDuration, Priority priority, std::string arrowResource)
	: super(AttackType::Damage, UIResources::Menus_Icons_Crossbow, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Multi)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	this->arrowResource = arrowResource;
	
	this->addChild(this->castSound);
}

CastArrowVolley::~CastArrowVolley()
{
}

void CastArrowVolley::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastArrowVolley::cloneInternal()
{
	return CastArrowVolley::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority, this->arrowResource);
}

LocalizedString* CastArrowVolley::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_ArrowVolley_ArrowVolley::create();
}

std::string CastArrowVolley::getAttackAnimation()
{
	return "AttackCast";
}

void CastArrowVolley::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	ObjectEvents::QueryObject<CinematicMarker>([=](CinematicMarker* marker)
	{
		ArrowVolley* arrowRain = ArrowVolley::create(owner, nullptr, this->arrowResource);

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
	PlatformerAttack::TagArenaTop,
	[=]()
	{
		// TOP CENTER ARENA MARKER NOT FOUND!
		ArrowVolley* arrowRain = ArrowVolley::create(owner, nullptr, this->arrowResource);

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
		arrowRain->setPosition(arrowRain->getPosition() + Vec2(-256.0f, 1024.0f));
	});
}

void CastArrowVolley::onCleanup()
{
}

bool CastArrowVolley::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (TimelineEntry* next : timeline->getEntries())
		{
			if (dynamic_cast<CastArrowVolley*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<ArrowVolley>([&](ArrowVolley*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastArrowVolley::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
