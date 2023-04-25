#include "FinchRescued.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Objects/DisabledPortal.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FinchRescued::MapKeyQuest = "finch-rescued";
const std::string FinchRescued::QuestTagShipPortal = "sky-ship-portal";
const std::string FinchRescued::PropertyIsReturnTrip = "is-return-trip";

FinchRescued* FinchRescued::create(GameObject* owner, QuestLine* questLine)
{
	FinchRescued* instance = new FinchRescued(owner, questLine);

	instance->autorelease();

	return instance;
}

FinchRescued::FinchRescued(GameObject* owner, QuestLine* questLine) : super(owner, questLine, FinchRescued::MapKeyQuest, false)
{
	this->owner = dynamic_cast<PlatformerEntity*>(owner);

	if (this->owner != nullptr)
	{
		this->isReturnTrip = GameUtils::getKeyOrDefault(this->owner->properties, FinchRescued::PropertyIsReturnTrip, Value(false)).asBool();
	}
}

FinchRescued::~FinchRescued()
{
}

void FinchRescued::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		this->portal = portal;

		if (questState != QuestState::None)
		{
			this->portal->getComponent<DisabledPortal>([=](DisabledPortal* disabledPortal)
			{
				disabledPortal->enablePortal();
			});
		}

	}, FinchRescued::QuestTagShipPortal);

	if (this->owner != nullptr)
	{
		if (questState == QuestState::None)
		{
			this->owner->despawn();
		}
		else
		{
			this->owner->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
			{
				LocalizedString* text = nullptr;

				if (this->isReturnTrip)
				{
					text = Strings::Platformer_Quests_CastleValgrind_SkyShipToCastle_Finch_CanWeBoardToCastle::create();
				}
				else
				{
					text = Strings::Platformer_Quests_CastleValgrind_SkyShipToCastle_Finch_CanWeBoardToTown::create();
				}

				interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
					text,
					[=]()
					{
						this->runYesSequence();
					}),
					0.5f
				);
			});
		}
	}
}

void FinchRescued::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void FinchRescued::onComplete()
{
}

void FinchRescued::onSkipped()
{
}

void FinchRescued::runYesSequence()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_SkyShipToCastle_Finch_Yep::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->owner, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}
