#include "TeachHackerModeDeprecated.h"

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
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/SoundResources.h"

#include "Strings/Platformer/Quests/EndianForest/Intro/Marcel/A_YoullNeverMakeIt.h"
#include "Strings/Platformer/Quests/EndianForest/Intro/Marcel/B_RedirectWind.h"
#include "Strings/Platformer/Quests/EndianForest/Intro/Marcel/C_TakeThisItem.h"
#include "Strings/Platformer/Quests/EndianForest/Intro/Marcel/D_MeetMeAtMagesGuild.h"

using namespace cocos2d;

const std::string TeachHackerModeDeprecated::MapKeyQuest = "teach-hacker-mode-deprecated";
const std::string TeachHackerModeDeprecated::TagQuestPortal = "quest-portal";
const std::string TeachHackerModeDeprecated::TagHelpTotemHacking = "help-totem-hacking";

TeachHackerModeDeprecated* TeachHackerModeDeprecated::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TeachHackerModeDeprecated* instance = new TeachHackerModeDeprecated(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TeachHackerModeDeprecated::TeachHackerModeDeprecated(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TeachHackerModeDeprecated::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->helpTotem = nullptr;
	this->portal = nullptr;
	this->marcel = nullptr;
	this->squally = nullptr;
	this->teleportSound = WorldSound::create(SoundResources::Platformer_Doors_Portals_Teleport);

	this->addChild(this->teleportSound);
}

TeachHackerModeDeprecated::~TeachHackerModeDeprecated()
{
}

void TeachHackerModeDeprecated::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<HelpTotem>(this, [=](HelpTotem* helpTotem)
	{
		this->helpTotem = helpTotem;
		this->helpTotem->deactivate();
	}, TeachHackerModeDeprecated::TagHelpTotemHacking);

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
		this->portal->disable();
		this->portal->closePortal(true);
	}, TeachHackerModeDeprecated::TagQuestPortal);
}

void TeachHackerModeDeprecated::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(TeachHackerModeDeprecated::MapKeyQuest, [=](ValueMap args)
	{
		this->runCinematicSequencePt1();
	});
}

void TeachHackerModeDeprecated::onComplete()
{
}

void TeachHackerModeDeprecated::onSkipped()
{
	this->removeAllListeners();
}

void TeachHackerModeDeprecated::runCinematicSequencePt1()
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
				this->teleportSound->play();
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

void TeachHackerModeDeprecated::runCinematicSequencePt2()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_Intro_Marcel_A_YoullNeverMakeIt::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->marcel, false),
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

void TeachHackerModeDeprecated::runCinematicSequencePt3()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_Intro_Marcel_B_RedirectWind::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->marcel, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePt4();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium1,
		false
	));
}

void TeachHackerModeDeprecated::runCinematicSequencePt4()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
	Strings::Platformer_Quests_EndianForest_Intro_Marcel_C_TakeThisItem::create(),
	DialogueEvents::DialogueVisualArgs(
		DialogueBox::DialogueDock::Bottom,
		DialogueBox::DialogueAlignment::Left,
		DialogueEvents::BuildPreviewNode(this->marcel, false),
		DialogueEvents::BuildPreviewNode(this->squally, true)
	),
	[=]()
	{
		this->runCinematicSequencePt5();
	},
	SoundResources::Platformer_Entities_Generic_ChatterMedium3,
	false
	));
}

void TeachHackerModeDeprecated::runCinematicSequencePt5()
{
	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_Intro_Marcel_D_MeetMeAtMagesGuild::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->marcel, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		),
		[=]()
		{
			PlatformerEvents::TriggerGiveItem(PlatformerEvents::GiveItemArgs(EssenceOfWind::create()));
			this->helpTotem->activate();
			this->complete();
			
			this->runAction(Sequence::create(
				CallFunc::create([=]()
				{
					this->marcel->runAction(FadeTo::create(1.0f, 0));
				}),
				DelayTime::create(2.0f),
				CallFunc::create([=]()
				{
					this->portal->closePortal(false);
				}),
				nullptr
			));
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium2,
		true
	));
}
