#include "EnterCrypts.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
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

const std::string EnterCrypts::MapKeyQuest = "enter-crypts";

EnterCrypts* EnterCrypts::create(GameObject* owner, QuestLine* questLine)
{
	EnterCrypts* instance = new EnterCrypts(owner, questLine);

	instance->autorelease();

	return instance;
}

EnterCrypts::EnterCrypts(GameObject* owner, QuestLine* questLine) : super(owner, questLine, EnterCrypts::MapKeyQuest, false)
{
	this->lightningStrike = SmartAnimationSequenceNode::create();
	this->lightningSound = Sound::create(SoundResources::Hexus_Attacks_Energy);

	this->lightningStrike->setVisible(false);

	this->addChild(this->lightningStrike);
	this->addChild(this->lightningSound);
}

EnterCrypts::~EnterCrypts()
{
}

void EnterCrypts::onLoad(QuestState questState)
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
				movementBehavior->setMoveAcceleration(EntityMovementBehavior::DefaultRunAcceleration);
			});
		}
	}, Perceptron::MapKey);

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

	if (questState != QuestState::Complete)
	{
		ObjectEvents::QueryObjects<Trigger>([&](Trigger* trigger)
		{
			trigger->getCollision()->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionData data)
			{
				if (GameUtils::getWorldCoords(this->squally).x > GameUtils::getWorldCoords(this->perceptron).x)
				{
					this->runCinematicSequenceStrikeZone();
				}

				return CollisionResult::DoNothing;
			});
		}, "strike-zone");
	}
}

void EnterCrypts::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce("gauntlet-start", [=](ValueMap valueMap)
	{
		this->runCinematicSequencePt1();

		ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* exit)
		{
			if (this->perceptron != nullptr)
			{
				this->perceptron->setState(StateKeys::CinematicHijacked, Value(true));
				this->perceptron->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->perceptron).x));
				this->perceptron->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(exit).x));
			}
		}, "exit");
	});

	this->listenForMapEventOnce("gauntlet-complete", [=](ValueMap valueMap)
	{
		this->complete();
	});
}

void EnterCrypts::onComplete()
{
}

void EnterCrypts::onSkipped()
{
	this->removeAllListeners();
}

void EnterCrypts::runCinematicSequencePt1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_LambdaCrypts_EnterCrypts_Scrappy_A_DangerDanger::create(),
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

void EnterCrypts::runCinematicSequenceStrikeZone()
{
	if (this->perceptron != nullptr)
	{
		this->perceptron->clearState(StateKeys::CinematicHijacked);
		this->perceptron->clearState(StateKeys::CinematicSourceX);
		this->perceptron->clearState(StateKeys::CinematicDestinationX);
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_LambdaCrypts_EnterCrypts_Perceptron_A_FoundYou::create(), 
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->perceptron, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			if (this->squally != nullptr)
			{
				// Kill with forced map reload to reset the event
				this->squally->getComponent<SquallyRespawnBehavior>([=](SquallyRespawnBehavior* respawnBehavior)
				{
					this->lightningStrike->setVisible(true);
					this->lightningStrike->playAnimation(FXResources::Lightning_Lightning_0000, 0.06f);
					GameUtils::setWorldCoords(this->lightningStrike, GameUtils::getWorldCoords(this->squally) + Vec2(0.0f, 392.0f));
					this->lightningSound->play();
					respawnBehavior->respawnWithMapReload();
				});
			}
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		true
	));
}
