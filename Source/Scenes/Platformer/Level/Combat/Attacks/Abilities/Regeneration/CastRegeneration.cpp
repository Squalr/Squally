#include "CastRegeneration.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/Regeneration/Regeneration.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastRegeneration* CastRegeneration::create(float attackDuration, float recoverDuration, Priority priority, std::string arrowResource)
{
	CastRegeneration* instance = new CastRegeneration(attackDuration, recoverDuration, priority, arrowResource);

	instance->autorelease();

	return instance;
}

CastRegeneration::CastRegeneration(float attackDuration, float recoverDuration, Priority priority, std::string arrowResource)
	: super(AttackType::Damage, UIResources::Menus_Icons_MoonShine, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Multi)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	this->arrowResource = arrowResource;
	
	this->addChild(this->castSound);
}

CastRegeneration::~CastRegeneration()
{
}

void CastRegeneration::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastRegeneration::cloneInternal()
{
	return CastRegeneration::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority, this->arrowResource);
}

LocalizedString* CastRegeneration::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Fortitude_Fortitude::create();
}

std::string CastRegeneration::getAttackAnimation()
{
	return "AttackCast";
}

void CastRegeneration::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	ObjectEvents::QueryObject<CinematicMarker>([=](CinematicMarker* marker)
	{
		Regeneration* arrowRain = Regeneration::create(owner, nullptr, this->arrowResource);

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
		Regeneration* arrowRain = Regeneration::create(owner, nullptr, this->arrowResource);

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

void CastRegeneration::onCleanup()
{
}

bool CastRegeneration::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (auto next : timeline->getEntries())
		{
			if (dynamic_cast<CastRegeneration*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<Regeneration>([&](Regeneration*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastRegeneration::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
