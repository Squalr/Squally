#include "PersuadeGuard.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Doors/PuzzleDoors/Gate/MulDoor/MulDoor.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/WeakMindedBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/BoredWithoutVisitors.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/DoorTech.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/FollowMe.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/GoingToTheInn.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Lycan/NoVisitors.h"

using namespace cocos2d;

const std::string PersuadeGuard::MapKeyQuest = "persuade-guard";
const std::string PersuadeGuard::QuestTagInn = "inn";
const std::string PersuadeGuard::TagSolidWall = "solid-wall";
const std::string PersuadeGuard::TagPrisonDoor = "prison-door";
const std::string PersuadeGuard::TagExit = "exit";
const std::string PersuadeGuard::EventExplainDoor = "explain-door";

PersuadeGuard* PersuadeGuard::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	PersuadeGuard* instance = new PersuadeGuard(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

PersuadeGuard::PersuadeGuard(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, PersuadeGuard::MapKeyQuest, questTag, false)
{
	this->lycan = dynamic_cast<Lycan*>(owner);
	this->solidWall = dynamic_cast<CollisionObject*>(owner);
	this->squally = nullptr;
	this->hasRunPersuasionSequence = false;
}

PersuadeGuard::~PersuadeGuard()
{
}

void PersuadeGuard::onEnter()
{
	super::onEnter();
}

void PersuadeGuard::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});

	ObjectEvents::watchForObject<MulDoor>(this, [=](MulDoor* mulDoor)
	{
		this->mulDoor = mulDoor;
	});
	
	ObjectEvents::watchForObject<CollisionObject>(this, [=](CollisionObject* solidWall)
	{
		this->solidWall = solidWall;

		if (this->solidWall != nullptr && questState == QuestState::Complete)
		{
			this->solidWall->setPhysicsEnabled(false);
		}
	}, PersuadeGuard::TagSolidWall);

	if (this->lycan != nullptr)
	{
		this->lycan->attachBehavior(LookAtSquallyBehavior::create(this->lycan));
	}

	if (questState == QuestState::Complete)
	{
		if (this->solidWall != nullptr)
		{
			this->solidWall->setPhysicsEnabled(false);
		}

		if (this->lycan != nullptr)
		{
			this->lycan->setVisible(false);
		}
	}
}

void PersuadeGuard::onActivate(bool isActiveThroughSkippable)
{
	if (this->lycan != nullptr)
	{
		this->lycan->attachBehavior(WeakMindedBehavior::create(this->lycan));

		this->lycan->listenForStateWrite(StateKeys::WeakMinded, [=](Value value)
		{
			if (value.asBool())
			{
				this->runPersuasionSequencePart1a();
			}
		});

		this->runNoVisitorsSequence();
	}

	this->listenForMapEvent(PersuadeGuard::EventExplainDoor, [=](ValueMap args)
	{
		this->runPersuasionSequencePart2a();
	});
}

void PersuadeGuard::onComplete()
{
	this->removeAllListeners();
}

void PersuadeGuard::onSkipped()
{
	this->removeAllListeners();
}

void PersuadeGuard::runNoVisitorsSequence()
{
	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicHijack();

			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_NoVisitors::create(),
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Right,
				[=]()
				{
				},
				DialogueEvents::BuildPreviewNode(this->squally, false),
				DialogueEvents::BuildPreviewNode(this->lycan, true)
			));
		}),
		nullptr
	));
}

void PersuadeGuard::runPersuasionSequencePart1a()
{
	if (this->hasRunPersuasionSequence)
	{
		return;
	}

	this->hasRunPersuasionSequence = true;

	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_BoredWithoutVisitors::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Right,
		[=]()
		{
			this->runPersuasionSequencePart1b();
		},
		DialogueEvents::BuildPreviewNode(this->squally, false),
		DialogueEvents::BuildPreviewNode(this->lycan, true)
	));
}

void PersuadeGuard::runPersuasionSequencePart1b()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_FollowMe::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Right,
		[=]()
		{
			this->runPersuasionSequencePart1c();
		},
		DialogueEvents::BuildPreviewNode(this->squally, false),
		DialogueEvents::BuildPreviewNode(this->lycan, true)
	));
}

void PersuadeGuard::runPersuasionSequencePart1c()
{
	PlatformerEvents::TriggerCinematicHijack();
	
	ObjectEvents::watchForObject<CinematicMarker>(this, [=](CinematicMarker* cinematicMarker)
	{
		if (this->solidWall != nullptr)
		{
			this->solidWall->setPhysicsEnabled(false);
		}

		this->lycan->setState(StateKeys::CinematicDestinationX, Value(cinematicMarker->getPositionX()));
	}, PersuadeGuard::TagPrisonDoor);

	this->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
		}),
		nullptr
	));
}

void PersuadeGuard::runPersuasionSequencePart2a()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_DoorTech::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Right,
		[=]()
		{
			this->runPersuasionSequencePart2b();
		},
		DialogueEvents::BuildPreviewNode(this->squally, false),
		DialogueEvents::BuildPreviewNode(this->lycan, true)
	));
}

void PersuadeGuard::runPersuasionSequencePart2b()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_Lycan_GoingToTheInn::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Right,
		[=]()
		{
			this->runPersuasionSequencePart2c();
		},
		DialogueEvents::BuildPreviewNode(this->squally, false),
		DialogueEvents::BuildPreviewNode(this->lycan, true)
	));
}

void PersuadeGuard::runPersuasionSequencePart2c()
{
	PlatformerEvents::TriggerCinematicRestore();

	ObjectEvents::watchForObject<CinematicMarker>(this, [=](CinematicMarker* cinematicMarker)
	{
		this->lycan->setState(StateKeys::CinematicDestinationX, Value(cinematicMarker->getPositionX()));
	}, PersuadeGuard::TagExit);

	this->lycan->listenForStateWrite(StateKeys::CinematicDestinationReached, [=](Value value)
	{
		this->lycan->runAction(FadeTo::create(1.0f, 0));
	});

	this->complete();
}
