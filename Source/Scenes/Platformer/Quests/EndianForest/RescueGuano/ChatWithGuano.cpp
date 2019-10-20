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
#include "Objects/Platformer/Doors/PuzzleDoors/Gate/MulDoor/MulDoor.h"

#include "Strings/Platformer/Ellipses.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/DoorTech.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/GetMeOutOfHere.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/WeShouldHelpHim.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/WhatGotMeInHere.h"

using namespace cocos2d;

const std::string ChatWithGuano::MapKeyQuest = "chat-with-guano";
const std::string ChatWithGuano::EventExplainDoor = "explain-door";

ChatWithGuano* ChatWithGuano::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	ChatWithGuano* instance = new ChatWithGuano(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

ChatWithGuano::ChatWithGuano(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, ChatWithGuano::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->guano = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

ChatWithGuano::~ChatWithGuano()
{
}

void ChatWithGuano::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	});

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	});

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});
}

void ChatWithGuano::onActivate(bool isActiveThroughSkippable)
{
	ObjectEvents::watchForObject<MulDoor>(this, [=](MulDoor* mulDoor)
	{
		this->mulDoor = mulDoor;
		this->mulDoor->toggleHackable(false);
	});

	this->listenForMapEvent(ChatWithGuano::EventExplainDoor, [=](ValueMap)
	{
		this->runChatSequence();
	});
}

void ChatWithGuano::onComplete()
{
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
			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_RescueGuano_GetMeOutOfHere::create(),
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Left,
				[=]()
				{
					this->runChatSequencePt2();
				},
				DialogueEvents::BuildPreviewNode(this->guano, false),
				DialogueEvents::BuildPreviewNode(this->squally, true),
				false
			));
		}),
		nullptr
	));
}

void ChatWithGuano::runChatSequencePt2()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::HardRight,
		[=]()
		{
			this->runChatSequencePt3();
		},
		DialogueEvents::BuildPreviewNode(this->guano, false),
		DialogueEvents::BuildPreviewNode(this->squally, true),
		false
	));
}

void ChatWithGuano::runChatSequencePt3()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_WhatGotMeInHere::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Left,
		[=]()
		{
			this->runChatSequencePt4();
		},
		DialogueEvents::BuildPreviewNode(this->guano, false),
		DialogueEvents::BuildPreviewNode(this->squally, true),
		false
	));
}

void ChatWithGuano::runChatSequencePt4()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_WeShouldHelpHim::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Left,
		[=]()
		{
			this->runChatSequencePt5();
		},
		DialogueEvents::BuildPreviewNode(this->scrappy, false),
		DialogueEvents::BuildPreviewNode(this->squally, true),
		true
	));
}

void ChatWithGuano::runChatSequencePt5()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_DoorTech::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Left,
		[=]()
		{
			this->runChatSequencePt6();
		},
		DialogueEvents::BuildPreviewNode(this->guano, false),
		DialogueEvents::BuildPreviewNode(this->squally, true),
		true
	));
}

void ChatWithGuano::runChatSequencePt6()
{
	this->mulDoor->toggleHackable(true);
	this->complete();
}
