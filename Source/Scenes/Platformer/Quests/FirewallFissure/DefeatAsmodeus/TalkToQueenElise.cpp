#include "TalkToQueenElise.h"

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
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/FirewallFissure/QueenElise.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToQueenElise::MapKeyQuest = "talk-to-queen-elise";
const std::string TalkToQueenElise::MapEventTalkToQueenElise = "talk-to-queen-elise";

TalkToQueenElise* TalkToQueenElise::create(GameObject* owner, QuestLine* questLine)
{
	TalkToQueenElise* instance = new TalkToQueenElise(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToQueenElise::TalkToQueenElise(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToQueenElise::MapKeyQuest, false)
{
}

TalkToQueenElise::~TalkToQueenElise()
{
}

void TalkToQueenElise::onLoad(QuestState questState)
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

	ObjectEvents::WatchForObject<QueenElise>(this, [=](QueenElise* queenElise)
	{
		this->queenElise = queenElise;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->queenElise->watchForComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableNewQuest();
			});
		}
	});

	if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
	{
		this->listenForMapEventOnce(TalkToQueenElise::MapEventTalkToQueenElise, [=](ValueMap)
		{
			this->runCinematicSequencePt1();
		});
	}
}

void TalkToQueenElise::onActivate(bool isActiveThroughSkippable)
{
}

void TalkToQueenElise::onComplete()
{	
	Objectives::SetCurrentObjective(ObjectiveKeys::DMDeliverLetter);

	if (this->queenElise != nullptr)
	{
		this->queenElise->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}
}

void TalkToQueenElise::onSkipped()
{
	this->removeAllListeners();
}

void TalkToQueenElise::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->queenElise, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		"",
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create()
			->setStringReplacementVariables(Strings::Platformer_MapNames_DataMines_Drammol::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt5();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->guano, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt6();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt6()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt7();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt7()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt8();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt8()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->guano, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt9();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt9()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt10();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt10()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->runCinematicSequencePt11();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt11()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->guano, false),
			DialogueEvents::BuildPreviewNode(&this->queenElise, true)
		),
		[=]()
		{
			this->complete();
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}
