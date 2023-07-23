#include "MinesPerceptronEncounter.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/VoidStar/Perceptron.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Npcs/Mages/Mabel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Movement/SquallyRespawnBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Components/Objects/Illusions/DispelIllusionBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MinesPerceptronEncounter::MapKeyQuest = "mines-perceptron-encounter";

MinesPerceptronEncounter* MinesPerceptronEncounter::create(GameObject* owner, QuestLine* questLine)
{
	MinesPerceptronEncounter* instance = new MinesPerceptronEncounter(owner, questLine);

	instance->autorelease();

	return instance;
}

MinesPerceptronEncounter::MinesPerceptronEncounter(GameObject* owner, QuestLine* questLine) : super(owner, questLine, MinesPerceptronEncounter::MapKeyQuest, false)
{
}

MinesPerceptronEncounter::~MinesPerceptronEncounter()
{
}

void MinesPerceptronEncounter::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Perceptron>(this, [=](Perceptron* perceptron)
	{
		this->perceptron = perceptron;
		
		if (questState == QuestState::Complete)
		{
			this->perceptron->despawn();
		}
		else
		{
			this->perceptron->getComponent<EntityMovementBehavior>([=](EntityMovementBehavior* movementBehavior)
			{
				movementBehavior->setMoveAcceleration(EntityMovementBehavior::DefaultSprintAcceleration);
			});
		}
	}, Perceptron::MapKey);
	
	ObjectEvents::WatchForObject<CameraTarget>(this, [=](CameraTarget* cameraTarget)
	{
		this->cinematicCameraTarget = cameraTarget;
	}, "cinematic");

	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Gecky>(this, [=](Gecky* gecky)
	{
		this->gecky = gecky;
	}, Gecky::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void MinesPerceptronEncounter::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	this->listenForMapEventOnce("gauntlet-start", [=](ValueMap valueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void MinesPerceptronEncounter::onComplete()
{
}

void MinesPerceptronEncounter::onSkipped()
{
	this->removeAllListeners();
}

void MinesPerceptronEncounter::runCinematicSequencePt1()
{
	if (this->perceptron == nullptr)
	{
		this->complete();
		return;
	}

	GameCamera::getInstance()->pushTarget(CameraTrackingData(this->perceptron, Vec2(0.0f, 192.0f), Vec2::ZERO, CameraTrackingData::CameraScrollType::Rectangle, CameraTrackingData::DefaultCameraFollowSpeed, 1.5f));

	// Patrol is broken into two segements for cinematic reasons (halfPoint + exit)
	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* halfPoint)
	{
		if (this->perceptron == nullptr)
		{
			this->complete();
			return;
		}

		this->perceptron->setState(StateKeys::CinematicHijacked, Value(true));
		this->perceptron->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->perceptron).x));
		this->perceptron->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(halfPoint).x));

		this->perceptron->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
		{
			this->broadcastMapEvent("bridge-group-B", ValueMap());

			// Continue to exit after half way point
			ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* exit)
			{
				if (this->perceptron != nullptr)
				{
					this->perceptron->setState(StateKeys::CinematicHijacked, Value(true));
					this->perceptron->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->perceptron).x));
					this->perceptron->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(exit).x));
					
					this->perceptron->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
					{
						this->runCinematicSequencePt2();
					});
				}
			}, "exit");
			
			// Adjust Squally to keep LoS once Perceptron patrols half way across hallway
			ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* adjustment)
			{
				if (this->squally != nullptr)
				{
					this->squally->setState(StateKeys::CinematicHijacked, Value(true));
					this->squally->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->perceptron).x));
					this->squally->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(adjustment).x));
					
					this->squally->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
					{
						this->squally->getAnimations()->setFlippedX(true);
					});
				}
			}, "adjustment");
		});
	}, "half-point");

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_DataMines_MinesPerceptronEncounter_A_StayHidden::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		false
	));
}

void MinesPerceptronEncounter::runCinematicSequencePt2()
{
	if (this->perceptron != nullptr)
	{
		GameCamera::getInstance()->popTarget();
		this->perceptron->despawn();
		this->complete();
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_DataMines_MinesPerceptronEncounter_B_Wonder::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		true
	));
}
