#include "TalkToHera.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Hera.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/FountainRoomKey.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToHera::MapKeyQuest = "talk-to-hera";

TalkToHera* TalkToHera::create(GameObject* owner, QuestLine* questLine)
{
	TalkToHera* instance = new TalkToHera(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToHera::TalkToHera(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToHera::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->hera = nullptr;
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

	ObjectEvents::WatchForObject<Hera>(this, [=](Hera* hera)
	{
		this->hera = hera;
		
		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->hera->clearState(StateKeys::PatrolDestinationX);
			this->hera->setState(StateKeys::PatrolHijacked, Value(true));
			this->hera->getAnimations()->playAnimation("Cower", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f, 0.5f, true));
			this->hera->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableTurnIn();
			});
		}
	}, Hera::MapKey);

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
	this->hera->getAttachedBehavior<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
	{
		questBehavior->enableIncompleteQuest();
	});

	Objectives::SetCurrentObjective(ObjectiveKeys::URExploreFountain);
}

void TalkToHera::onSkipped()
{
	this->removeAllListeners();
}

void TalkToHera::runCinematicSequence()
{
	if (this->hera == nullptr)
	{
		return;
	}
	
	this->hera->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_A_StayAway::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
				this->hera->setState(StateKeys::PatrolHijacked, Value(false));
				this->hera->getAnimations()->clearAnimationPriority();
				this->hera->getAnimations()->playAnimation();

				if (GameUtils::getWorldCoords(this->hera).x > GameUtils::getWorldCoords(this->squally).x)
				{
					this->hera->getAnimations()->setFlippedX(true);
				}
				else
				{
					this->hera->getAnimations()->setFlippedX(false);
				}
			},
			Voices::GetNextVoiceShort(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_B_Oh::create()
				->setStringReplacementVariables(Strings::Platformer_MapNames_UnderflowRuins_Athens::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_C_WhatHappened::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_D_Medusa::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_E_Slay::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_F_NotAChance::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_G_Yes::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_H_BetterOffInJail::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Hera_I_TakeThisKey::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->hera, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItem(PlatformerEvents::GiveItemArgs(FountainRoomKey::create()));
				this->complete();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}
