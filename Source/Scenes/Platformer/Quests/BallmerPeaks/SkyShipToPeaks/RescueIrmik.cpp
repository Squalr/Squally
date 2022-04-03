#include "RescueIrmik.h"

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
#include "Entities/Platformer/Npcs/Transition/Irmik.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Huds/FadeHuds/FadeHud.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RescueIrmik::MapKeyQuest = "rescue-irmik";
const std::string RescueIrmik::MapEventIrmikRescued = "irmik-rescued";
const std::string RescueIrmik::TagIrmikExit = "irmik-exit";
const std::string RescueIrmik::TagCutscenePortal = "cutscene-portal";

RescueIrmik* RescueIrmik::create(GameObject* owner, QuestLine* questLine)
{
	RescueIrmik* instance = new RescueIrmik(owner, questLine);

	instance->autorelease();

	return instance;
}

RescueIrmik::RescueIrmik(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RescueIrmik::MapKeyQuest, false)
{
}

RescueIrmik::~RescueIrmik()
{
}

void RescueIrmik::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Irmik>(this, [=](Irmik* irmik)
	{
		this->irmik = irmik;

		if (questState == QuestState::Complete)
		{
			this->irmik->despawn();
		}
	}, Irmik::MapKey);

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
	}, RescueIrmik::TagCutscenePortal);
}

void RescueIrmik::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(RescueIrmik::MapEventIrmikRescued, [=](ValueMap)
	{
		this->runCinematicSequencePart1();
	});
}

void RescueIrmik::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::EFReturnToQueen);
}

void RescueIrmik::onSkipped()
{
	this->removeAllListeners();
}

void RescueIrmik::runCinematicSequencePart1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Menus_StoryMode::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->irmik, true)
		),
		[=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Ellipses::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->irmik, true),
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

void RescueIrmik::runCinematicSequencePart2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Menus_StoryMode::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->irmik, true)
		),
		[=]()
		{
			this->runCinematicSequencePart3();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		false
	));
}

void RescueIrmik::runCinematicSequencePart3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Menus_StoryMode::create()
			->setStringReplacementVariables(Strings::Menus_StoryMode::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->irmik, true)
		),
		[=]()
		{
			this->runCinematicSequencePart4();
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}

void RescueIrmik::runCinematicSequencePart4()
{
	if (this->irmik == nullptr)
	{
		return;
	}

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* marker)
	{
		this->irmik->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords3D(this->irmik).x));
		this->irmik->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(marker).x));

		this->irmik->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
		{
			this->irmik->despawn();
		});
	}, RescueIrmik::TagIrmikExit);

	this->complete();
}
