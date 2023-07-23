#include "TalkToPrincessDawn.h"

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
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/DataMines/PrincessDawn.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/DataMines/LetterForThePrincess.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToPrincessDawn::MapKeyQuest = "talk-to-princess-dawn";
const std::string TalkToPrincessDawn::MapTagCinematicGecky = "cinematic-gecky";

TalkToPrincessDawn* TalkToPrincessDawn::create(GameObject* owner, QuestLine* questLine)
{
	TalkToPrincessDawn* instance = new TalkToPrincessDawn(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToPrincessDawn::TalkToPrincessDawn(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToPrincessDawn::MapKeyQuest, false)
{
}

TalkToPrincessDawn::~TalkToPrincessDawn()
{
}

void TalkToPrincessDawn::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Gecky>(this, [=](Gecky* gecky)
	{
		this->gecky = gecky;
		
		if (questState != QuestState::Active && questState != QuestState::ActiveThroughSkippable)
		{
			this->gecky->despawn();
		}
		else
		{
			this->enqueueGeckyDialogue();
		}

		// Disable gecky from appearing on party menu
		this->gecky->setQueryable(false);
	}, TalkToPrincessDawn::MapTagCinematicGecky);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<PrincessDawn>(this, [=](PrincessDawn* princessDawn)
	{
		this->princessDawn = princessDawn;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->princessDawn->watchForComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableTurnIn();
			});
		}
	});

	if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
	{
		this->runCinematicSequencePt1();
	}
}

void TalkToPrincessDawn::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void TalkToPrincessDawn::onComplete()
{	
	Objectives::SetCurrentObjective(ObjectiveKeys::DMInvestigatePowerOutage);

	if (this->princessDawn != nullptr)
	{
		this->princessDawn->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}
}

void TalkToPrincessDawn::onSkipped()
{
	this->removeAllListeners();
}

void TalkToPrincessDawn::enqueueGeckyDialogue()
{
	this->gecky->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_Gecky_A_Hi::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->gecky, true)
			),
			[=]()
			{
				this->defer([=]()
				{
					this->enqueueGeckyDialogue();
				});
			},
			Voices::GetNextVoiceShort(),
			true
		));
	});
}

void TalkToPrincessDawn::runCinematicSequencePt1()
{
	this->princessDawn->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_A_LetterForYou::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(LetterForThePrincess::create(), false));
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_B_ThankYou::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_C_CouldNotFindCause::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceLong(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_D_WithoutPower::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_E_InvestigateCause::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceLong(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_F_Nope::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_G_OfCourse::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_H_TakeGecky::create()
				->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_DataMines_Gecky::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceLong(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_I_Hi::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->gecky, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_J_WelcomeToTheCrew::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->gecky, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_K_ImOut::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				// Backwards compat, this field was added mid development, and we want to avoid Guano being inaccessible to old patches
				SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGuanoFound, Value(true));
				SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGeckyFound, Value(true));
				this->squally->setState(StateKeys::CurrentHelper, Value(Gecky::MapKey));

				// Despawn cinematic Gecky
				if (this->gecky != nullptr)
				{
					this->gecky->despawn();
				}

				LocalizedString* hintString = Strings::Platformer_Help_HelpTotemGecky::create();
				LocalizedString* helperNameString = Strings::Platformer_Entities_Names_Helpers_DataMines_Gecky::create();
				LocalizedString* bracketString1 = Strings::Common_Brackets::create();
				LocalizedString* shiftString = Strings::Input_Shift::create();

				bracketString1->setStringReplacementVariables(shiftString);
				hintString->setStringReplacementVariables({ helperNameString, bracketString1 });
				
				NotificationEvents::TriggerNotificationTakeover(NotificationEvents::NotificationTakeoverArgs(
					Strings::Platformer_Notifications_Party_HelperJoinedParty::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_DataMines_Gecky::create()),
					hintString,
					SoundResources::Notifications_NotificationGood1
				));

				this->complete();
			},
			Voices::GetNextVoiceShort(),
			true
		));
	});
}