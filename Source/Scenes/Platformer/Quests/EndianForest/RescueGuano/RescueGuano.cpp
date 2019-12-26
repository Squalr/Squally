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
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RescueGuano::MapKeyQuest = "rescue-guano";
const std::string RescueGuano::EventMulDoorUnlocked = "mul-door-unlocked";
const std::string RescueGuano::TagPrisonDoor = "prison-door";

RescueGuano* RescueGuano::create(GameObject* owner, QuestLine* questLine)
{
	RescueGuano* instance = new RescueGuano(owner, questLine);

	instance->autorelease();

	return instance;
}

RescueGuano::RescueGuano(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RescueGuano::MapKeyQuest, false)
{
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
			this->defer([=]()
			{
				this->guano->despawn();
			});
		}
	}, Guano::MapKeyGuano);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
}

void RescueGuano::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(RescueGuano::EventMulDoorUnlocked, [=](ValueMap args)
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
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_RescueGuano_E_Freedom::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true),
				true
			),
			[=]()
			{
				this->runRescueSequencePt2();
			},
			SoundResources::Platformer_Entities_Generic_ChatterCheer1,
			false
		));
	}, RescueGuano::TagPrisonDoor);
}

void RescueGuano::runRescueSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_F_NotMuchOfAFighter::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->guano, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runRescueSequencePt3();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium1,
		false
	));
}

void RescueGuano::runRescueSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_RescueGuano_G_HelpYouFindThings::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->guano, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
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
			this->squally->setState(StateKeys::CurrentHelper, Value(Guano::MapKeyGuano));
			this->complete();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium2,
		true
	));
}
