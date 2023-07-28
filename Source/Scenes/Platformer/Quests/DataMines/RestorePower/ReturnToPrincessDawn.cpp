#include "ReturnToPrincessDawn.h"

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
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/DataMines/PrincessDawn.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/DataMines/TrainTicket.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReturnToPrincessDawn::MapKeyQuest = "return-to-princess-dawn";

ReturnToPrincessDawn* ReturnToPrincessDawn::create(GameObject* owner, QuestLine* questLine)
{
	ReturnToPrincessDawn* instance = new ReturnToPrincessDawn(owner, questLine);

	instance->autorelease();

	return instance;
}

ReturnToPrincessDawn::ReturnToPrincessDawn(GameObject* owner, QuestLine* questLine) : super(owner, questLine, ReturnToPrincessDawn::MapKeyQuest, false)
{
}

ReturnToPrincessDawn::~ReturnToPrincessDawn()
{
}

void ReturnToPrincessDawn::onLoad(QuestState questState)
{
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

void ReturnToPrincessDawn::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void ReturnToPrincessDawn::onComplete()
{	
	Objectives::SetCurrentObjective(ObjectiveKeys::DMRideTrainToCastleValgrind);

	PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(TrainTicket::create()));
	PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ TrainTicket::create() }));

	if (this->princessDawn != nullptr)
	{
		this->princessDawn->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}
}

void ReturnToPrincessDawn::onSkipped()
{
	this->removeAllListeners();
}

void ReturnToPrincessDawn::runCinematicSequencePt1()
{
	this->princessDawn->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->dockToTop();
		
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_Q_PowerRestoredThankYou::create(),
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
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_R_TakeTrainTicket::create(),
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
			Strings::Platformer_Quests_DataMines_RestorePower_PrincessDawn_S_DontForgetBlacksmith::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->princessDawn, true)
			),
			[=]()
			{
				this->complete();
			},
			Voices::GetNextVoiceLong(),
			false
		));
	});
}
