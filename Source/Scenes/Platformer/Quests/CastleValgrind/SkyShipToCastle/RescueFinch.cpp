#include "RescueFinch.h"

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
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/Transition/Finch.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RescueFinch::MapKeyQuest = "rescue-finch";
const std::string RescueFinch::MapEventFinchRescued = "finch-rescued";
const std::string RescueFinch::TagFinchExit = "finch-exit";
const std::string RescueFinch::TagCutscenePortal = "cutscene-portal";

RescueFinch* RescueFinch::create(GameObject* owner, QuestLine* questLine)
{
	RescueFinch* instance = new RescueFinch(owner, questLine);

	instance->autorelease();

	return instance;
}

RescueFinch::RescueFinch(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RescueFinch::MapKeyQuest, false)
{
}

RescueFinch::~RescueFinch()
{
}

void RescueFinch::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Finch>(this, [=](Finch* finch)
	{
		this->finch = finch;

		if (questState == QuestState::Complete)
		{
			this->finch->despawn();
		}
	}, Finch::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* cutscenePortal)
	{
		this->cutscenePortal = cutscenePortal;
	}, RescueFinch::TagCutscenePortal);
}

void RescueFinch::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(RescueFinch::MapEventFinchRescued, [=](ValueMap)
	{
		this->runCinematicSequencePart1();
	});
}

void RescueFinch::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::EFReturnToQueen);
}

void RescueFinch::onSkipped()
{
	this->removeAllListeners();
}

void RescueFinch::runCinematicSequencePart1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Menus_StoryMode::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->finch, true)
		),
		[=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Ellipses::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->finch, true),
					true
				),
				[=]()
				{
					this->runCinematicSequencePart2();
				},
				"",
				false
			));
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void RescueFinch::runCinematicSequencePart2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Menus_StoryMode::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->finch, true)
		),
		[=]()
		{
			this->runCinematicSequencePart3();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		false
	));
}

void RescueFinch::runCinematicSequencePart3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Menus_StoryMode::create()
			->setStringReplacementVariables(Strings::Menus_StoryMode::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->finch, true)
		),
		[=]()
		{
			this->runCinematicSequencePart4();
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}

void RescueFinch::runCinematicSequencePart4()
{
	if (this->finch == nullptr)
	{
		return;
	}

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* marker)
	{
		this->finch->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords3D(this->finch).x));
		this->finch->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(marker).x));

		this->finch->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
		{
			this->finch->despawn();
		});
	}, RescueFinch::TagFinchExit);

	this->complete();
}
