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
#include "Entities/Platformer/Npcs/EndianForest/Marcel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

#include "Strings/Platformer/Quests/EndianForest/Intro/Marcel/BendReality.h"
#include "Strings/Platformer/Quests/EndianForest/Intro/Marcel/MeetMeAtMagesGuild.h"
#include "Strings/Platformer/Quests/EndianForest/Intro/Marcel/TakeThisItem.h"

using namespace cocos2d;

const std::string TeachHackerMode::MapKeyQuest = "teach-hacker-mode";
const std::string TeachHackerMode::TagQuestPortal = "quest-portal";
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
	this->portal = nullptr;
	this->marcel = nullptr;
	this->squally = nullptr;
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

	ObjectEvents::watchForObject<Marcel>(this, [=](Marcel* marcel)
	{
		this->marcel = marcel;
		this->marcel->setOpacity(0);
	}, Marcel::MapKeyMarcel);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;
		this->portal->lock();
		this->portal->closePortal(true);
	}, TeachHackerMode::TagQuestPortal);
}

void TeachHackerMode::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(TeachHackerMode::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

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

	if (this->marcel != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->portal->openPortal(false);
			}),
			DelayTime::create(2.0f),
			CallFunc::create([=]()
			{
				this->marcel->runAction(FadeTo::create(1.0f, 255));
				this->portal->openPortal(false);
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
		Strings::Platformer_Quests_EndianForest_Intro_Marcel_BendReality::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->marcel, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		),
		[=]()
		{
			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_Intro_Marcel_TakeThisItem::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(this->marcel, false),
					DialogueEvents::BuildPreviewNode(this->squally, true)
				),
				[=]()
				{
					DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_EndianForest_Intro_Marcel_MeetMeAtMagesGuild::create(),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Bottom,
							DialogueBox::DialogueAlignment::Left,
							DialogueEvents::BuildPreviewNode(this->marcel, false),
							DialogueEvents::BuildPreviewNode(this->squally, true)
						),
						[=]()
						{
							this->helpTotem->activate();
							this->portal->closePortal(false);
							this->marcel->runAction(FadeTo::create(1.0f, 0));
						},
						true
					));
				},
				false
			));
		},
		false
	));
}
