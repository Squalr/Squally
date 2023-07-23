#include "PerceptronEncounter.h"

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

const std::string PerceptronEncounter::MapKeyQuest = "perceptron-encounter";

PerceptronEncounter* PerceptronEncounter::create(GameObject* owner, QuestLine* questLine)
{
	PerceptronEncounter* instance = new PerceptronEncounter(owner, questLine);

	instance->autorelease();

	return instance;
}

PerceptronEncounter::PerceptronEncounter(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PerceptronEncounter::MapKeyQuest, false)
{
	this->lightningStrike = SmartAnimationSequenceNode::create();
	this->lightningSound = Sound::create(SoundResources::Hexus_Attacks_Energy);

	this->lightningStrike->setVisible(false);

	this->addChild(this->lightningStrike);
	this->addChild(this->lightningSound);
}

PerceptronEncounter::~PerceptronEncounter()
{
}

void PerceptronEncounter::onLoad(QuestState questState)
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
			this->perceptron->setVisible(false);
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

	ObjectEvents::WatchForObject<PlatformerEntity>(this, [=](PlatformerEntity* platformerEntity)
	{
		this->cinematicKillTarget = platformerEntity;

		if (questState != QuestState::Complete)
		{
			this->cinematicKillTarget->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				// Defer to let initial health behavior load properly
				this->defer([=]()
				{
					healthBehavior->revive();
				});
			});
		}
	}, "cinematic-kill-target");

	if (questState != QuestState::Complete)
	{
		ObjectEvents::QueryObjects<Trigger>([&](Trigger* trigger)
		{
			trigger->getCollision()->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionData data)
			{
				this->isInSafeZone = true;
				return CollisionResult::DoNothing;
			});
			trigger->getCollision()->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionData data)
			{
				this->isInSafeZone = false;
				return CollisionResult::DoNothing;
			});
		}, "safe-zone");

		ObjectEvents::QueryObjects<Trigger>([&](Trigger* trigger)
		{
			trigger->getCollision()->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionData data)
			{
				if (this->chaseInProgress)
				{
					this->runCinematicSequenceStrikeZone();
				}
				return CollisionResult::DoNothing;
			});
		}, "strike-zone");
	}
}

void PerceptronEncounter::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	this->listenForMapEventOnce("gauntlet-start", [=](ValueMap valueMap)
	{
		this->runCinematicSequencePt1();
	});

	this->scheduleUpdate();
}

void PerceptronEncounter::onComplete()
{
}

void PerceptronEncounter::onSkipped()
{
	this->removeAllListeners();
}

void PerceptronEncounter::update(float dt)
{
	super::update(dt);

	if (this->chaseInProgress)
	{
		this->elapsedChaseTime += dt;

		Vec2 squallyPos =  GameUtils::getWorldCoords(this->squally);
		Vec2 perceptronPos =  GameUtils::getWorldCoords(this->perceptron);

		if (!this->sprintActive && this->elapsedChaseTime > 4.0f)
		{
			this->perceptron->getComponent<EntityMovementBehavior>([&](EntityMovementBehavior* movementBehavior)
			{
				movementBehavior->setMoveAcceleration(EntityMovementBehavior::DefaultSprintAcceleration);
				this->sprintActive = true;
			});
		}

		if (this->elapsedChaseTime > 15.0f)
		{
			// Time's up. Success if in safe area, or have already snuck past Perceptron
			if (this->isInSafeZone || squallyPos.x > perceptronPos.x)
			{
				if (this->perceptron != nullptr)
				{
					this->perceptron->despawn();
				}
				this->chaseInProgress = false;
				this->runCinematicSequencePt2();
			}
			// Otherwise death
			else
			{
				this->runCinematicSequenceStrikeZone();
			}
		}
		// Kill if Squally within 1024 frontal distance (and some backwards distance) and not hidden
		else if (!this->isInSafeZone
			&& squallyPos.x < perceptronPos.x + 312.0f
			&& squallyPos.x > perceptronPos.x - 1280.0f)
		{
			this->runCinematicSequenceStrikeZone();
		}
	}
}

void PerceptronEncounter::runCinematicSequencePt1()
{
	if (this->cinematicKillTarget != nullptr)
	{
		GameUtils::setWorldCoords(this->lightningStrike, GameUtils::getWorldCoords(this->cinematicKillTarget) + Vec2(0.0f, 460.0f));
		this->lightningStrike->setVisible(true);
		this->lightningStrike->playAnimation(FXResources::Lightning_Lightning_0000, 0.06f);
		this->lightningSound->play();

		this->cinematicKillTarget->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->kill();
		});
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_PerceptronChase_A_DangerDanger::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* exit)
			{
				if (this->perceptron != nullptr)
				{
					this->perceptron->setVisible(true);
					this->perceptron->setState(StateKeys::CinematicHijacked, Value(true));
					this->perceptron->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->perceptron).x));
					this->perceptron->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(exit).x));
				}
			}, "exit");

			this->chaseInProgress = true;
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		true
	));
}

void PerceptronEncounter::runCinematicSequenceStrikeZone()
{
	this->chaseInProgress = false;

	if (this->perceptron != nullptr)
	{
		this->perceptron->clearState(StateKeys::CinematicHijacked);
		this->perceptron->clearState(StateKeys::CinematicSourceX);
		this->perceptron->clearState(StateKeys::CinematicDestinationX);
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_PerceptronChase_B_FoundYou::create(), 
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
		Voices::GetNextVoiceShort(Voices::VoiceType::Ghost),
		true
	));
}

void PerceptronEncounter::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_PerceptronChase_C_Whew::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		true
	));
}

void PerceptronEncounter::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_PerceptronChase_D_JustRun::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->complete();
		},
		Voices::GetNextVoiceLong(Voices::VoiceType::Droid),
		true
	));
}
