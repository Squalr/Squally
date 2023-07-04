#include "WelcomeToFirewall.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Entities/Platformer/Npcs/FirewallFissure/Ash.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Quests/FirewallFissure/ReleasePressure/ReleasePressure.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WelcomeToFirewall::MapKeyQuest = "welcome-to-ff";

WelcomeToFirewall* WelcomeToFirewall::create(GameObject* owner, QuestLine* questLine)
{
	WelcomeToFirewall* instance = new WelcomeToFirewall(owner, questLine);

	instance->autorelease();

	return instance;
}

WelcomeToFirewall::WelcomeToFirewall(GameObject* owner, QuestLine* questLine) : super(owner, questLine, WelcomeToFirewall::MapKeyQuest, false)
{
}

WelcomeToFirewall::~WelcomeToFirewall()
{
}

void WelcomeToFirewall::onEnter()
{
	super::onEnter();
}

void WelcomeToFirewall::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Ash>(this, [=](Ash* ash)
	{
		this->ash = ash;

		this->attachAshBehavior();
	}, Ash::MapKey);
}

void WelcomeToFirewall::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void WelcomeToFirewall::attachAshBehavior()
{
	if (this->ash == nullptr)
	{
		return;
	}

	this->ash->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_Ash_A_WhatAreYouDoingHere::create(),
			[=]()
			{
				if (this->questLine->isCompleteUpToInclusive(ReleasePressure::MapKeyQuest))
				{
					DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_Ash_S_StudyPortal::create(),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Bottom,
							DialogueBox::DialogueAlignment::Right,
							DialogueEvents::BuildPreviewNode(&this->squally, false),
							DialogueEvents::BuildPreviewNode(&this->ash, true)
						),
						[=]()
						{
						},
						Voices::GetNextVoiceLong()
					));
				}
				else
				{
					DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_Ash_B_FirewallFissure::create()
							->setStringReplacementVariables(Strings::Platformer_MapNames_FirewallFissure_Brimstone::create()),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Bottom,
							DialogueBox::DialogueAlignment::Right,
							DialogueEvents::BuildPreviewNode(&this->squally, false),
							DialogueEvents::BuildPreviewNode(&this->ash, true)
						),
						[=]()
						{
							DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
								Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_Ash_C_TownToLeft::create(),
								DialogueEvents::DialogueVisualArgs(
									DialogueBox::DialogueDock::Bottom,
									DialogueBox::DialogueAlignment::Right,
									DialogueEvents::BuildPreviewNode(&this->squally, false),
									DialogueEvents::BuildPreviewNode(&this->ash, true)
								),
								[=]()
								{
								},
								Voices::GetNextVoiceLong()
							));
						},
						Voices::GetNextVoiceLong()
					));
				}
			}),
			1.0f
		);
	});
}

void WelcomeToFirewall::onComplete()
{
}

void WelcomeToFirewall::onSkipped()
{
	this->removeAllListeners();
}
