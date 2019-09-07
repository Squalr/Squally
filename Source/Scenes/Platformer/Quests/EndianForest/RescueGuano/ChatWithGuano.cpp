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
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Doors/PuzzleDoors/Gate/MulDoor/MulDoor.h"

#include "Strings/Platformer/Ellipses.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/GetMeOutOfHere.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/WeShouldHelpHim.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/WhatGotMeInHere.h"

using namespace cocos2d;

const std::string ChatWithGuano::MapKeyQuest = "chat-with-guano";

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

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});

	ObjectEvents::watchForObject<MulDoor>(this, [=](MulDoor* mulDoor)
	{
		this->mulDoor = mulDoor;
		this->mulDoor->toggleHackable(false);
	});
}

void ChatWithGuano::onActivate(bool isActiveThroughSkippable)
{
	this->runChatSequence();
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
	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicHijack();

			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_RescueGuano_GetMeOutOfHere::create(),
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Left,
				[=]()
				{
					this->runChatSequencePt2();
				},
				DialogueEvents::BuildPreviewNode(this->guano, false),
				DialogueEvents::BuildPreviewNode(this->squally, true)
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
		DialogueEvents::BuildPreviewNode(this->squally, true)
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
		DialogueEvents::BuildPreviewNode(this->squally, true)
	));
}

void ChatWithGuano::runChatSequencePt4()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_WhatShouldHelpHim::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Left,
		[=]()
		{
			this->mulDoor->toggleHackable(true);
			PlatformerEvents::TriggerCinematicRestore();
		},
		DialogueEvents::BuildPreviewNode(this->guano, false),
		DialogueEvents::BuildPreviewNode(this->squally, true)
	));
}
