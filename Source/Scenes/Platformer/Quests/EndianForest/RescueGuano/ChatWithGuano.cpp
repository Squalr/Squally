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

#include "Resources/SoundResources.h"

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
	ObjectEvents::watchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKeyGuano);

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<MulDoor>(this, [=](MulDoor* mulDoor)
	{
		this->mulDoor = mulDoor;
	}, MulDoor::MapKeyMulDoor);
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
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Top,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(this->guano, false),
					DialogueEvents::BuildPreviewNode(this->squally, true)
				),
				[=]()
				{
					this->runChatSequencePt2();
				},
				SoundResources::Platformer_Entities_Generic_ChatterMedium2,
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
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::HardRight,
			DialogueEvents::BuildPreviewNode(this->guano, false),
			DialogueEvents::BuildPreviewNode(this->squally, true),
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
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_WhatGotMeInHere::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->guano, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		),
		[=]()
		{
			this->runChatSequencePt4();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium3,
		false
	));
}

void ChatWithGuano::runChatSequencePt4()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_WeShouldHelpHim::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->scrappy, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		),
		[=]()
		{
			this->runChatSequencePt5();
		},
		SoundResources::Platformer_Entities_Droid_DroidBrief2,
		true
	));
}

void ChatWithGuano::runChatSequencePt5()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_DoorTech::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->guano, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		),
		[=]()
		{
			this->mulDoor->toggleHackable(true);
			this->complete();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium4,
		true
	));
}
