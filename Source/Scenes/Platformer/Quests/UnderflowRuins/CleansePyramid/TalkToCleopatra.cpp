#include "TalkToCleopatra.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Cleopatra.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToCleopatra::MapKeyQuest = "talk-to-cleopatra";
const std::string TalkToCleopatra::TagExitPortal = "exit-portal";

TalkToCleopatra* TalkToCleopatra::create(GameObject* owner, QuestLine* questLine)
{
	TalkToCleopatra* instance = new TalkToCleopatra(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToCleopatra::TalkToCleopatra(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToCleopatra::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->cleopatra = nullptr;
}

TalkToCleopatra::~TalkToCleopatra()
{
}

void TalkToCleopatra::onLoad(QuestState questState)
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

	ObjectEvents::WatchForObject<Cleopatra>(this, [=](Cleopatra* cleopatra)
	{
		this->cleopatra = cleopatra;
	});

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		if (questState != QuestState::Complete)
		{
			portal->lock(false);
		}
	}, TalkToCleopatra::TagExitPortal);

	if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
	{
		this->listenForMapEventOnce(TalkToCleopatra::MapKeyQuest, [=](ValueMap)
		{
			this->runCinematicSequencePt1();
		});
	}
}

void TalkToCleopatra::onActivate(bool isActiveThroughSkippable)
{
}

void TalkToCleopatra::onComplete()
{
	SaveManager::SaveProfileData(SaveKeys::SaveKeySpellBookHoly, Value(true));
	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
	
	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Platformer_Spellbooks_SpellbookAcquired::create(),
		Strings::Platformer_Spellbooks_SpellbookHoly::create(),
		ItemResources::Spellbooks_SpellBookHoly,
		SoundResources::Notifications_NotificationGood1
	));
	
	Objectives::SetCurrentObjective(ObjectiveKeys::UREnterTheMines);

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		portal->unlock(false);
	}, TalkToCleopatra::TagExitPortal);
}

void TalkToCleopatra::onSkipped()
{
	this->removeAllListeners();
}

void TalkToCleopatra::runCinematicSequencePt1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CleansePyramid_Cleopatra_A_YouHaveCleansed::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->cleopatra, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToCleopatra::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->cleopatra, true),
			true
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		"",
		false
	));
}

void TalkToCleopatra::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CleansePyramid_Cleopatra_B_TakeThis::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->cleopatra, true)
		),
		[=]()
		{
			// We complete here to trigger giving the items and saving
			this->complete();

			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceLong(),
		true
	));
}

void TalkToCleopatra::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CleansePyramid_Cleopatra_C_BehindMeDataMines::create()
			->setStringReplacementVariables(Strings::Platformer_MapNames_DataMines_DataMines::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->cleopatra, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceLong(),
		true
	));
}

void TalkToCleopatra::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CleansePyramid_Cleopatra_D_BestOfLuck::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->cleopatra, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceLong(),
		true
	));
}
