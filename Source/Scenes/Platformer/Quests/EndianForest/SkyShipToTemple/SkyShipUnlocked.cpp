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

const std::string SkyShipUnlocked::MapKeyQuest = "sky-ship-unlocked";
const std::string SkyShipUnlocked::QuestTagShipPortal = "sky-ship-portal";

SkyShipUnlocked* SkyShipUnlocked::create(GameObject* owner, QuestLine* questLine)
{
	SkyShipUnlocked* instance = new SkyShipUnlocked(owner, questLine);

	instance->autorelease();

	return instance;
}

SkyShipUnlocked::SkyShipUnlocked(GameObject* owner, QuestLine* questLine) : super(owner, questLine, SkyShipUnlocked::MapKeyQuest, false)
{
	this->owner = dynamic_cast<PlatformerEntity*>(owner);
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
		this->owner->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				Strings::Menus_StoryMode::create()
					->setStringReplacementVariables(Strings::Platformer_MapNames_UnderflowRuins_UnderflowRuins::create()),
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

void SkyShipUnlocked::onActivate(bool isActiveThroughSkippable)
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
		Strings::Menus_StoryMode::create(),
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
		Strings::Menus_StoryMode::create(),
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
