#include "RescueGuano.h"

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
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Strings/Platformer/Quests/EndianForest/RescueGuano/Freedom.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/NotMuchOfAFighter.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/HelpYouFindThings.h"

using namespace cocos2d;

const std::string RescueGuano::MapKeyQuest = "rescue-guano";
const std::string RescueGuano::EventMulDoorUnlocked = "mul-door-unlocked";
const std::string RescueGuano::TagPrisonDoor = "prison-door";

RescueGuano* RescueGuano::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	RescueGuano* instance = new RescueGuano(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

RescueGuano::RescueGuano(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, RescueGuano::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->guano = nullptr;
	this->squally = nullptr;
}

RescueGuano::~RescueGuano()
{
}

void RescueGuano::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;

		if (questState == QuestState::Complete)
		{
			this->guano->despawn();
		}
	});

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});
}

void RescueGuano::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(RescueGuano::EventMulDoorUnlocked, [=](ValueMap args)
	{
		this->runRescueSequence();
	});
}

void RescueGuano::onComplete()
{
}

void RescueGuano::onSkipped()
{
	this->removeAllListeners();
}

void RescueGuano::runRescueSequence()
{	
	ObjectEvents::watchForObject<CinematicMarker>(this, [=](CinematicMarker* cinematicMarker)
	{
		DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_RescueGuano_Freedom::create(),
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			[=]()
			{
				this->runRescueSequencePt2();
			},
			DialogueEvents::BuildPreviewNode(this->guano, false),
			DialogueEvents::BuildPreviewNode(this->squally, true),
			false
		));
	}, RescueGuano::TagPrisonDoor);
}

void RescueGuano::runRescueSequencePt2()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_NotMuchOfAFighter::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Left,
		[=]()
		{
			this->runRescueSequencePt3();
		},
		DialogueEvents::BuildPreviewNode(this->guano, false),
		DialogueEvents::BuildPreviewNode(this->squally, true),
		false
	));
}

void RescueGuano::runRescueSequencePt3()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_HelpYouFindThings::create(),
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Left,
		[=]()
		{
			this->guano->runAction(Sequence::create(
				FadeTo::create(1.0f, 0),
				CallFunc::create([=]()
				{
					this->guano->despawn();	
				}),
				nullptr
			));
			HelperEvents::TriggerChangeHelper(HelperEvents::ChangeHelperArgs(Guano::MapKeyGuano));
			this->complete();
		},
		DialogueEvents::BuildPreviewNode(this->guano, false),
		DialogueEvents::BuildPreviewNode(this->squally, true),
		true
	));
}
