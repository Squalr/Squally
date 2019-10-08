#include "BeatTutorialA.h"

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
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/GetMeOutOfHere.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/WeShouldHelpHim.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/WhatGotMeInHere.h"

using namespace cocos2d;

const std::string BeatTutorialA::MapKeyQuest = "beat-tutorial-A";

BeatTutorialA* BeatTutorialA::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	BeatTutorialA* instance = new BeatTutorialA(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

BeatTutorialA::BeatTutorialA(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, BeatTutorialA::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->guano = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

BeatTutorialA::~BeatTutorialA()
{
}

void BeatTutorialA::onLoad(QuestState questState)
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

void BeatTutorialA::onActivate(bool isActiveThroughSkippable)
{
	ObjectEvents::watchForObject<MulDoor>(this, [=](MulDoor* mulDoor)
	{
		this->mulDoor = mulDoor;
		this->mulDoor->toggleHackable(false);
	});

	this->runChatSequence();
}

void BeatTutorialA::onComplete()
{
}

void BeatTutorialA::onSkipped()
{
	this->removeAllListeners();
}

void BeatTutorialA::runChatSequence()
{
	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		DelayTime::create(3.0f),
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

void BeatTutorialA::runChatSequencePt2()
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

void BeatTutorialA::runChatSequencePt3()
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

void BeatTutorialA::runChatSequencePt4()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_WeShouldHelpHim::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Left,
		[=]()
		{
			this->mulDoor->toggleHackable(true);
			this->complete();
		},
		DialogueEvents::BuildPreviewNode(this->scrappy, false),
		DialogueEvents::BuildPreviewNode(this->squally, true),
		true
	));
}
