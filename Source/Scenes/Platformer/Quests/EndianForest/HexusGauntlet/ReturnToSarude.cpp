#include "ReturnToSarude.h"

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
#include "Entities/Platformer/Npcs/DataMines/Sarude.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/Gauntlet/SarudeTutorialBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/Gauntlet/SarudeTutorialSkipBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReturnToSarude::MapKeyQuest = "return-to-sarude";
const std::string ReturnToSarude::QuestPortalTag = "quest-portal";

ReturnToSarude* ReturnToSarude::create(GameObject* owner, QuestLine* questLine)
{
	ReturnToSarude* instance = new ReturnToSarude(owner, questLine);

	instance->autorelease();

	return instance;
}

ReturnToSarude::ReturnToSarude(GameObject* owner, QuestLine* questLine) : super(owner, questLine, ReturnToSarude::MapKeyQuest, false)
{
	this->sarude = nullptr;
	this->squally = nullptr;
	this->portal = nullptr;
}

ReturnToSarude::~ReturnToSarude()
{
}

void ReturnToSarude::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;
	}, Sarude::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;
		
		if (questState == QuestState::Active || questState == QuestState::Complete)
		{
			this->portal->closePortal(true);
		}
	}, ReturnToSarude::QuestPortalTag);
}

void ReturnToSarude::onActivate(bool isActiveThroughSkippable)
{
	this->defer([=]()
	{
		this->registerDialogue(isActiveThroughSkippable);
	});
}

void ReturnToSarude::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::EFExplorePrison);
}

void ReturnToSarude::onSkipped()
{
	this->removeAllListeners();
}

void ReturnToSarude::registerDialogue(bool isActiveThroughSkippable)
{
	if (this->sarude != nullptr)
	{
		if (!isActiveThroughSkippable)
		{
			this->sarude->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
			{
				// Pre-text chain
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_K_IChallengeYou::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->sarude, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
					},
					Voices::GetNextVoiceShort(),
					true
				));
			});
		}

		HexusBehaviorBase* behavior = isActiveThroughSkippable 
			? (HexusBehaviorBase*)SarudeTutorialSkipBehavior::create(this->sarude)
			: (HexusBehaviorBase*)SarudeTutorialBehavior::create(this->sarude);

		behavior->registerWinCallback([=]()
		{
			this->onHexusWin();
		});

		behavior->registerLossCallback([=]()
		{
			this->onHexusLoss();
		});

		behavior->registerDrawCallback([=]()
		{
			this->onHexusLoss();
		});

		this->sarude->attachBehavior(behavior);
	}
}

void ReturnToSarude::onHexusWin()
{
	this->complete();
	this->runPostHexusMatchCleanup();
	this->runDialogueIntroWin();
}

void ReturnToSarude::onHexusLoss()
{
	this->sarude->watchForAttachedBehavior<HexusBehaviorBase>([=](HexusBehaviorBase* hexusBehavior)
	{
		if (hexusBehavior->getLosses() + hexusBehavior->getDraws() >= 2)
		{
			hexusBehavior->giveItems();

			this->complete();
			this->runPostHexusMatchCleanup();
			this->runDialogueIntroLoss();
		}
	});
}

void ReturnToSarude::runDialogueIntroWin()
{
	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_M_WellDone::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->sarude, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runDialogueOutro();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void ReturnToSarude::runPostHexusMatchCleanup()
{
	if (this->portal != nullptr)
	{
		this->portal->closePortal(false);
	}

	this->sarude->watchForAttachedBehavior<HexusBehaviorBase>([=](HexusBehaviorBase* hexusBehavior)
	{
		hexusBehavior->removeFromDialogue();
	});
}

void ReturnToSarude::runDialogueIntroLoss()
{
	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_M_ValliantEffort::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->sarude, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runDialogueOutro();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void ReturnToSarude::runDialogueOutro()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
	Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_N_WeBroughtYouHere::create(),
	DialogueEvents::DialogueVisualArgs(
		DialogueBox::DialogueDock::Top,
		DialogueBox::DialogueAlignment::Left,
		DialogueEvents::BuildPreviewNode(&this->sarude, false),
		DialogueEvents::BuildPreviewNode(&this->squally, true)
	),
	[=]()
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_O_CompleteYourTraining::create()
			->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_EndianForest_Scrappy::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->sarude, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_P_LearnMoreOfTheseMonsters::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			true
			));
		},
		Voices::GetNextVoiceMedium(),
		false
		));
	},
	Voices::GetNextVoiceMedium(),
	false
	));
}
