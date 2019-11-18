#include "TeachHackerMode.h"

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
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string TeachHackerMode::MapKeyQuest = "teach-hacker-mode-deprecated";
const std::string TeachHackerMode::TagHelpTotemHacking = "help-totem-hacking";

TeachHackerMode* TeachHackerMode::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TeachHackerMode* instance = new TeachHackerMode(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TeachHackerMode::TeachHackerMode(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TeachHackerMode::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->helpTotem = nullptr;
	this->squally = nullptr;
	this->scrappy = nullptr;
}

TeachHackerMode::~TeachHackerMode()
{
}

void TeachHackerMode::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<HelpTotem>(this, [=](HelpTotem* helpTotem)
	{
		this->helpTotem = helpTotem;
		this->helpTotem->deactivate();
	}, TeachHackerMode::TagHelpTotemHacking);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* squally)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);
}

void TeachHackerMode::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(TeachHackerMode::MapKeyQuest, [=](ValueMap args)
	{
		this->runCinematicSequencePt1();
	});
}

void TeachHackerMode::onComplete()
{
}

void TeachHackerMode::onSkipped()
{
	this->removeAllListeners();
}

void TeachHackerMode::runCinematicSequencePt1()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;

	if (this->scrappy != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->runAction(Sequence::create(
			CallFunc::create([=]()
			{
			}),
			DelayTime::create(2.0f),
			CallFunc::create([=]()
			{
			}),
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
				this->runCinematicSequencePt2();
			}),
			nullptr
		));
	}
}

void TeachHackerMode::runCinematicSequencePt2()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		nullptr, // Strings::Platformer_Quests_EndianForest_Intro_Marcel_A_YoullNeverMakeIt::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->scrappy, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		SoundResources::Platformer_Entities_Generic_ChatterShort1,
		false
	));
}

void TeachHackerMode::runCinematicSequencePt3()
{
}

void TeachHackerMode::runCinematicSequencePt4()
{
}

void TeachHackerMode::runCinematicSequencePt5()
{
}
