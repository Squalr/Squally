#include "SkyShipUnlocked.h"

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
#include "Objects/Platformer/Transportation/Airship.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Objects/DisabledPortal.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkyShipUnlocked::MapKeyQuest = "sky-ship-unlocked";
const std::string SkyShipUnlocked::QuestTagShipPortal = "sky-ship-portal-temple";
const std::string SkyShipUnlocked::PropertyIsReturnTrip = "is-return-trip";
const std::string SkyShipUnlocked::QuestTagTempleAirship = "temple-airship";

SkyShipUnlocked* SkyShipUnlocked::create(GameObject* owner, QuestLine* questLine)
{
	SkyShipUnlocked* instance = new SkyShipUnlocked(owner, questLine);

	instance->autorelease();

	return instance;
}

SkyShipUnlocked::SkyShipUnlocked(GameObject* owner, QuestLine* questLine) : super(owner, questLine, SkyShipUnlocked::MapKeyQuest, false)
{
	this->owner = dynamic_cast<PlatformerEntity*>(owner);

	if (this->owner != nullptr)
	{
		this->isReturnTrip = GameUtils::getKeyOrDefault(this->owner->properties, SkyShipUnlocked::PropertyIsReturnTrip, Value(false)).asBool();
	}
}

SkyShipUnlocked::~SkyShipUnlocked()
{
}

void SkyShipUnlocked::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	if (questState == QuestState::None && this->isReturnTrip)
	{
		ObjectEvents::WatchForObject<Airship>(this, [=](Airship* airship)
		{
			airship->despawn();
		}, SkyShipUnlocked::QuestTagTempleAirship);
	}

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		this->portal = portal;

		if (questState != QuestState::None)
		{
			this->portal->getComponent<DisabledPortal>([=](DisabledPortal* disabledPortal)
			{
				disabledPortal->enablePortal();
			});

			this->complete();
		}

	}, SkyShipUnlocked::QuestTagShipPortal);

	if (this->owner != nullptr)
	{
		if (questState == QuestState::None && this->isReturnTrip)
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
					text = Strings::Platformer_Quests_EndianForest_SkyShipToTemple_Dudly_CanWeBoardToTown::create();
				}
				else
				{
					text = Strings::Platformer_Quests_EndianForest_SkyShipToTemple_Dudly_CanWeBoardToTemple::create();
				}

				interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
					text,
					[=]()
					{
						switch(questState)
						{
							case QuestState::Active:
							case QuestState::ActiveThroughSkippable:
							case QuestState::Complete:
							{
								this->runYesSequence();
								break;
							}
							case QuestState::None:
							{
								this->runNoSequence();
								break;
							}
						}
					}),
					0.5f
				);
			});
		}
	}
}

void SkyShipUnlocked::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void SkyShipUnlocked::onComplete()
{
}

void SkyShipUnlocked::onSkipped()
{
}

void SkyShipUnlocked::runNoSequence()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_SkyShipToTemple_Dudly_Nope::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->owner, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			Objectives::SetCurrentObjective(ObjectiveKeys::EFVisitQueen);
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}

void SkyShipUnlocked::runYesSequence()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_SkyShipToTemple_Dudly_Yep::create(),
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
