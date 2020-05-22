#include "TalkToHera.h"

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
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToHera::MapKeyQuest = "talk-to-hera";
const std::string TalkToHera::TagExitDoor = "exit-door";

TalkToHera* TalkToHera::create(GameObject* owner, QuestLine* questLine)
{
	TalkToHera* instance = new TalkToHera(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToHera::TalkToHera(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToHera::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->aphrodite = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

TalkToHera::~TalkToHera()
{
}

void TalkToHera::onLoad(QuestState questState)
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
			}, TalkToHera::TagExitDoor);
		}
	}, Aphrodite::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void TalkToHera::onActivate(bool isActiveThroughSkippable)
{
	this->runCinematicSequence();
}

void TalkToHera::onComplete()
{
	this->aphrodite->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		questBehavior->disableNewQuest();
	});

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* exitDoor)
	{
		exitDoor->unlock();
	}, TalkToHera::TagExitDoor);

	Objectives::SetCurrentObjective(ObjectiveKeys::URHeadToTown);
}

void TalkToHera::onSkipped()
{
	this->removeAllListeners();
}

void TalkToHera::runCinematicSequence()
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
				DialogueEvents::BuildPreviewNode(&this->aphrodite, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterShort1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_B_WhichWayToTown::create()
				->setStringReplacementVariables(Strings::Platformer_MapNames_UnderflowRuins_Athens::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->aphrodite, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Droid_DroidChatter,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_C_HeadThroughBack::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->aphrodite, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium2,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_D_OneFavor::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->aphrodite, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium4,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_E_Charity::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::HardRight,
				DialogueEvents::BuildPreviewNode(&this->aphrodite, false),
				DialogueEvents::BuildPreviewNode(&this->guano, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium3,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_F_WhatDoYouAsk::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::HardRight,
				DialogueEvents::BuildPreviewNode(&this->aphrodite, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_G_TalkToAlch::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->aphrodite, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
				this->complete();
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium2,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Aphrodite_H_WillDo::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::HardRight,
				DialogueEvents::BuildPreviewNode(&this->aphrodite, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Droid_DroidChatter,
			true
		));
	});
}
