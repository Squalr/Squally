#include "ChatWithGuano.h"

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
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/MulDoor/MulDoor.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ChatWithGuano::MapKeyQuest = "chat-with-guano";
const std::string ChatWithGuano::EventExplainDoor = "explain-door";

ChatWithGuano* ChatWithGuano::create(GameObject* owner, QuestLine* questLine)
{
	ChatWithGuano* instance = new ChatWithGuano(owner, questLine);

	instance->autorelease();

	return instance;
}

ChatWithGuano::ChatWithGuano(GameObject* owner, QuestLine* questLine) : super(owner, questLine, ChatWithGuano::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->mulDoor = nullptr;
}

ChatWithGuano::~ChatWithGuano()
{
}

void ChatWithGuano::onLoad(QuestState questState)
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

	ObjectEvents::WatchForObject<MulDoor>(this, [=](MulDoor* mulDoor)
	{
		this->mulDoor = mulDoor;
	}, MulDoor::MapKey);
}

void ChatWithGuano::onActivate(bool isActiveThroughSkippable)
{
	if (this->mulDoor != nullptr)
	{
		this->mulDoor->toggleHackable(false);
	}

	this->listenForMapEventOnce(ChatWithGuano::EventExplainDoor, [=](ValueMap)
	{
		this->runChatSequence();
	});
}

void ChatWithGuano::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::EFRescueGuano);
}

void ChatWithGuano::onSkipped()
{
	this->removeAllListeners();
}

void ChatWithGuano::runChatSequence()
{
	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_RescueGuano_A_GetMeOutOfHere::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->guano, true)
				),
				[=]()
				{
					this->runChatSequencePt2();
				},
				Voices::GetNextVoiceLong(),
				false
			));
		}),
		nullptr
	));
}

void ChatWithGuano::runChatSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true),
			true
		),
		[=]()
		{
			this->runChatSequencePt3();
		},
		"",
		false
	));
}

void ChatWithGuano::runChatSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_B_WhatGotMeInHere::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true)
		),
		[=]()
		{
			this->runChatSequencePt4();
		},
		Voices::GetNextVoiceLong(),
		false
	));
}

void ChatWithGuano::runChatSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_C_WeShouldHelpHim::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runChatSequencePt5();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		true
	));
}

void ChatWithGuano::runChatSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_D_DoorTech::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true)
		),
		[=]()
		{
			this->mulDoor->toggleHackable(true);
			this->complete();
		},
		Voices::GetNextVoiceLong(),
		true
	));
}
