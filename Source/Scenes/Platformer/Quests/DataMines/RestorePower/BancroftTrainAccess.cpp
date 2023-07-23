#include "BancroftTrainAccess.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/DataMines/Bancroft.h"
#include "Entities/Platformer/Npcs/DataMines/Mildred.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Doors/Warp.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/DataMines/LetterForThePrincess.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/CastleValgrind/CryptKey.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BancroftTrainAccess::MapKeyQuest = "bancroft-train-access";
const std::string BancroftTrainAccess::TagTrainWarp = "train-warp";

BancroftTrainAccess* BancroftTrainAccess::create(GameObject* owner, QuestLine* questLine)
{
	BancroftTrainAccess* instance = new BancroftTrainAccess(owner, questLine);

	instance->autorelease();

	return instance;
}

BancroftTrainAccess::BancroftTrainAccess(GameObject* owner, QuestLine* questLine) : super(owner, questLine, BancroftTrainAccess::MapKeyQuest, false)
{
}

BancroftTrainAccess::~BancroftTrainAccess()
{
}

void BancroftTrainAccess::onLoad(QuestState questState)
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

		// Nested due to squally inventory dependency
		ObjectEvents::WatchForObject<Mildred>(this, [=](Mildred* mildred)
		{
			this->mildred = mildred;

			// Wait for inventory to load
			this->defer([=]()
			{
				this->setMildredText();
			}, 1);
		}, Mildred::MapKey);
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Bancroft>(this, [=](Bancroft* bancroft)
	{
		this->bancroft = bancroft;

		this->bancroft->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				Strings::Platformer_Quests_DataMines_RestorePower_Bancroft_A_CanWeBoard::create(),
				[=]()
				{
					if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
					{
						this->runCinematicSequencePt1();
					}
					else
					{
						this->runCinematicSequenceAccessBlockedPt1();
					}
				}),
				1.0f
			);
		});
	});

	if (questState == QuestState::None)
	{
		ObjectEvents::WatchForObject<Warp>(this, [=](Warp* warp)
		{
			this->warp = warp;
			this->warp->disable();
		}, BancroftTrainAccess::TagTrainWarp);
	}
}

void BancroftTrainAccess::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void BancroftTrainAccess::onComplete()
{	
	if (this->bancroft != nullptr)
	{
		this->bancroft->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}
}

void BancroftTrainAccess::onSkipped()
{
	this->removeAllListeners();
}

void BancroftTrainAccess::setMildredText()
{
	if (this->mildred == nullptr)
	{
		return;
	}
	this->mildred->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		this->squally->watchForComponent<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			// Having the crypt key is a good proxy for "has cleared Castle Valgrind"
			if (entityInventoryBehavior->getInventory()->hasItemOfType<CryptKey>())
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_DataMines_RestorePower_Mildred_S_BraveHero::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->mildred, true)
					),
					[=]()
					{
						this->defer([=]()
						{
							this->setMildredText();
						});
					},
					Voices::GetNextVoiceLong(),
					true
				));
			}
			else
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_DataMines_RestorePower_Mildred_A_CastleHaunted::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->mildred, true)
					),
					[=]()
					{
						this->defer([=]()
						{
							this->setMildredText();
						});
					},
					Voices::GetNextVoiceLong(),
					true
				));
			}
		});
	});
}

void BancroftTrainAccess::runCinematicSequenceAccessBlockedPt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_DataMines_RestorePower_Bancroft_B_Nope::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->bancroft, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequenceAccessBlockedPt2();
		},
		Voices::GetNextVoiceLong(),
		false
	));
}

void BancroftTrainAccess::runCinematicSequenceAccessBlockedPt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_DataMines_RestorePower_Bancroft_C_WhereCanWeGetOne::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->bancroft, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequenceAccessBlockedPt3();
		},
		Voices::GetNextVoiceShort(),
		false
	));
}

void BancroftTrainAccess::runCinematicSequenceAccessBlockedPt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_DataMines_RestorePower_Bancroft_D_SoldOut::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->bancroft, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequenceAccessBlockedPt4();
		},
		Voices::GetNextVoiceShort(),
		false
	));
}

void BancroftTrainAccess::runCinematicSequenceAccessBlockedPt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_DataMines_RestorePower_Bancroft_E_AnythingWeCanDo::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->bancroft, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequenceAccessBlockedPt5();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void BancroftTrainAccess::runCinematicSequenceAccessBlockedPt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_DataMines_RestorePower_Bancroft_F_AskQueen::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->bancroft, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			Objectives::SetCurrentObjective(ObjectiveKeys::DMObtainTrainTicket);
			PlatformerEvents::TriggerCinematicRestore();
		},
		Voices::GetNextVoiceLong(),
		false
	));
}

void BancroftTrainAccess::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_DataMines_RestorePower_Bancroft_Q_Yep::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->bancroft, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}
