#include "TalkToElriel.h"

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
#include "Entities/Platformer/Npcs/EndianForest/Elriel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToElriel::MapKeyQuest = "talk-to-elriel";
const std::string TalkToElriel::TagElrielExit = "elriel-exit";

TalkToElriel* TalkToElriel::create(GameObject* owner, QuestLine* questLine)
{
	TalkToElriel* instance = new TalkToElriel(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToElriel::TalkToElriel(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToElriel::MapKeyQuest, false)
{
	this->elriel = nullptr;
	this->squally = nullptr;
}

TalkToElriel::~TalkToElriel()
{
}

void TalkToElriel::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Elriel>(this, [=](Elriel* elriel)
	{
		this->elriel = elriel;

		if (questState == QuestState::Complete)
		{
			this->elriel->despawn();
		}
	}, Elriel::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void TalkToElriel::onActivate(bool isActiveThroughSkippable)
{
	this->defer([=]()
	{
		this->runCinematicSequencePart1();
	});
}

void TalkToElriel::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::EFReturnToQueen);
}

void TalkToElriel::onSkipped()
{
	this->removeAllListeners();
}

void TalkToElriel::runCinematicSequencePart1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Elriel_A_GratefulYouAreHere::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->elriel, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Ellipses::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Top,
					DialogueBox::DialogueAlignment::HardRight,
					DialogueEvents::BuildPreviewNode(&this->elriel, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true),
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
		SoundResources::Platformer_Entities_Generic_ChatterMedium1,
		false
	));
}

void TalkToElriel::runCinematicSequencePart2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Elriel_B_AliveAndWell::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::HardRight,
			DialogueEvents::BuildPreviewNode(&this->elriel, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePart3();
		},
		SoundResources::Platformer_Entities_Droid_DroidBrief2,
		false
	));
}

void TalkToElriel::runCinematicSequencePart3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Elriel_C_MeetMeInTown::create()
			->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_Elbridge::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->elriel, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePart4();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium4,
		true
	));
}

void TalkToElriel::runCinematicSequencePart4()
{
	if (this->elriel == nullptr)
	{
		return;
	}

	this->complete();

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* marker)
	{
		this->elriel->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(marker).x));
	}, TalkToElriel::TagElrielExit);
}
