#include "TalkToAphrodite.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Aphrodite.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/CureTown.h"
#include "Scenes/Platformer/Quests/UnderflowRuins/CureTown/CureTownLine.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToAphrodite::MapKeyQuest = "talk-to-aphrodite";
const std::string TalkToAphrodite::TagExitDoor = "exit-door";
const std::string TalkToAphrodite::SaveKeyItemGiven = "APHRODITE_ITEM_GIVEN";

TalkToAphrodite* TalkToAphrodite::create(GameObject* owner, QuestLine* questLine)
{
	TalkToAphrodite* instance = new TalkToAphrodite(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToAphrodite::TalkToAphrodite(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToAphrodite::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->aphrodite = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

TalkToAphrodite::~TalkToAphrodite()
{
}

void TalkToAphrodite::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Aphrodite>(this, [=](Aphrodite* aphrodite)
	{
		this->aphrodite = aphrodite;
		
		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->aphrodite->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableNewQuest();
			});
		}
		else if (questState == QuestState::Complete)
		{
			ObjectEvents::WatchForObject<Portal>(this, [=](Portal* exitDoor)
			{
				exitDoor->unlock();
			}, TalkToAphrodite::TagExitDoor);

			this->runShipmentsComplete();
		}
	}, Aphrodite::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void TalkToAphrodite::onActivate(bool isActiveThroughSkippable)
{
	this->runCinematicSequence();
}

void TalkToAphrodite::onComplete()
{
	this->aphrodite->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		questBehavior->disableAll();
	});

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* exitDoor)
	{
		exitDoor->unlock();
	}, TalkToAphrodite::TagExitDoor);

	Objectives::SetCurrentObjective(ObjectiveKeys::URHeadToTown);
}

void TalkToAphrodite::onSkipped()
{
	this->removeAllListeners();
}

void TalkToAphrodite::runCinematicSequence()
{
	if (this->aphrodite == nullptr)
	{
		return;
	}
	
	this->aphrodite->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_A_Greetings::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_B_WhichWayToTown::create()
				->setStringReplacementVariables(Strings::Platformer_MapNames_UnderflowRuins_Athens::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_C_HeadThroughBack::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_D_OneFavor::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_E_Charity::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_F_WhatDoYouAsk::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_G_TalkToAlch::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
			),
			[=]()
			{
				this->complete();
			},
			Voices::GetNextVoiceLong(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_H_WillDo::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
			true
		));
	});
}

void TalkToAphrodite::runShipmentsComplete()
{
	bool griffinCured = QuestTask::GetQuestSaveStateOrDefault(CureTownLine::MapKeyQuestLine, CureTown::MapKeyQuest, CureTown::SaveKeyGriffinCured, Value(false)).asBool();
	
	if (griffinCured && !this->aphrodite->loadObjectStateOrDefault(TalkToAphrodite::SaveKeyItemGiven, Value(false)).asBool())
	{
		this->aphrodite->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_T_Shipments::create()
					->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Griffin::create()),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->aphrodite, true)
				),
				[=]()
				{
					PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ GarnetBand::create() }));
					this->aphrodite->saveObjectState(TalkToAphrodite::SaveKeyItemGiven, Value(true));
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});
	}
}
