#include "GauntletIntroduction.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Cleopatra.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Mounts/GatlingGun/GatlingGun.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GauntletIntroduction::MapKeyQuest = "gauntlet-introduction";
const std::string GauntletIntroduction::TagGuard = "guard";
const std::string GauntletIntroduction::TagGuardTeleport = "guard-teleport";
const std::string GauntletIntroduction::TagGuardArrive = "guard-arrive";
const std::string GauntletIntroduction::TagGuardLeave = "guard-leave";
const std::string GauntletIntroduction::TagSquallyDestination = "squally-destination";
const std::string GauntletIntroduction::MapEventBeginGauntlet = "begin-gauntlet";

GauntletIntroduction* GauntletIntroduction::create(GameObject* owner, QuestLine* questLine)
{
	GauntletIntroduction* instance = new GauntletIntroduction(owner, questLine);

	instance->autorelease();

	return instance;
}

GauntletIntroduction::GauntletIntroduction(GameObject* owner, QuestLine* questLine) : super(owner, questLine, GauntletIntroduction::MapKeyQuest, false)
{
}

GauntletIntroduction::~GauntletIntroduction()
{
}

void GauntletIntroduction::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<GatlingGun>(this, [=](GatlingGun* gatlingGun)
	{
		this->gatlingGun = gatlingGun;
	}, GatlingGun::MapKey);

	ObjectEvents::WatchForObject<Cleopatra>(this, [=](Cleopatra* cleopatra)
	{
		this->cleopatra = cleopatra;

		ObjectEvents::QueryObjects<PlatformerEntity>([=](PlatformerEntity* guard)
		{
			this->guards.push_back(guard);
		}, GauntletIntroduction::TagGuard);
	});

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* guardTeleportMarker)
	{
		this->guardTeleportMarker = guardTeleportMarker;
	}, GauntletIntroduction::TagGuardTeleport);

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* guardArriveMarker)
	{
		this->guardArriveMarker = guardArriveMarker;
	}, GauntletIntroduction::TagGuardArrive);

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* guardLeaveMarker)
	{
		this->guardLeaveMarker = guardLeaveMarker;
	}, GauntletIntroduction::TagGuardLeave);

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* squallyDestinationMarker)
	{
		this->squallyDestinationMarker = squallyDestinationMarker;
	}, GauntletIntroduction::TagSquallyDestination);

	if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
	{
		this->listenForMapEventOnce(GauntletIntroduction::MapKeyQuest, [=](ValueMap)
		{
			this->runCinematicSequencePt1();
		});
	}
}

void GauntletIntroduction::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void GauntletIntroduction::onComplete()
{
}

void GauntletIntroduction::onSkipped()
{
	this->removeAllListeners();
}

void GauntletIntroduction::runCinematicSequencePt1()
{
	if (this->gatlingGun != nullptr)
	{
		this->gatlingGun->playGauntletTrack();
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CleansePyramid_ColosseumGauntlet_Cleopatra_A_NewChallengersApproach::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->cleopatra, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void GauntletIntroduction::runCinematicSequencePt2()
{
	for (int index = 0; index < int(this->guards.size()); index++)
	{
		PlatformerEntity* guard = this->guards[index];

		if (guard == nullptr && this->guardTeleportMarker == nullptr)
		{
			continue;
		}

		Vec3 warpPosition = GameUtils::getWorldCoords3D(this->guardTeleportMarker);
		warpPosition.x += float(index) * 128.0f;

		PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(guard, warpPosition, false));
		guard->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(guard).x));
		guard->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(this->guardArriveMarker).x + float(index) * 128.0f));

		guard->getComponent<EntityMovementBehavior>([=](EntityMovementBehavior* movementBehavior)
		{
			movementBehavior->setMoveAcceleration(12000.0f);
		});
	}
	
	this->runAction(Sequence::create(
		DelayTime::create(1.75f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
			this->squally->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->squally).x));
			this->squally->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(this->squallyDestinationMarker).x));
			this->squally->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
			{
				PlatformerEvents::TriggerCinematicHijack();
				this->runCinematicSequencePt3();
			});
		}),
		nullptr
	));
}

void GauntletIntroduction::runCinematicSequencePt3()
{
	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
			this->broadcastMapEvent(GauntletIntroduction::MapEventBeginGauntlet, ValueMap());

			for (PlatformerEntity* guard : this->guards)
			{
				if (guard != nullptr)
				{
					guard->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(guard).x));
					guard->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(this->guardLeaveMarker).x));
					guard->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
					{
						guard->despawn();
					});
				}
			}
		}),
		nullptr
	));
}
