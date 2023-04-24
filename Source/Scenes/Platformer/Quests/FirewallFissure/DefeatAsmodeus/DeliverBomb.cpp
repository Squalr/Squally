#include "DeliverBomb.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/FirewallFissure/Scaldor.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DeliverBomb::MapKeyQuest = "deliver-bomb";

DeliverBomb* DeliverBomb::create(GameObject* owner, QuestLine* questLine)
{
	DeliverBomb* instance = new DeliverBomb(owner, questLine);

	instance->autorelease();

	return instance;
}

DeliverBomb::DeliverBomb(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DeliverBomb::MapKeyQuest, false)
{
}

DeliverBomb::~DeliverBomb()
{
}

void DeliverBomb::onLoad(QuestState questState)
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

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			// A bit lazy, ensures Scaldor is available by delaying 1 frame
			this->defer([=]()
			{
				this->runCinematicSequencePt1();
			});
		}
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scaldor>(this, [=](Scaldor* scaldor)
	{
		this->scaldor = scaldor;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->scaldor->watchForComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableTurnIn();
			});
		}
	});
}

void DeliverBomb::onActivate(bool isActiveThroughSkippable)
{
}

void DeliverBomb::onComplete()
{	
	Objectives::SetCurrentObjective(ObjectiveKeys::DMInvestigatePowerOutage);

	if (this->scaldor != nullptr)
	{
		this->scaldor->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}
}

void DeliverBomb::onSkipped()
{
	this->removeAllListeners();
}

void DeliverBomb::runCinematicSequencePt1()
{
	if (this->squally == nullptr)
	{
		return;
	}
	
	this->squally->watchForComponent<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
	{
		this->scaldor->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			if (entityInventoryBehavior->getInventory()->hasItemOfType<HeliumBomb>())
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::TODO::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->scrappy, false),
						DialogueEvents::BuildPreviewNode(&this->scaldor, true)
					),
					[=]()
					{
						PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(HeliumBomb::create()));
					},
					Voices::GetNextVoiceMedium(),
					false
				));

				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::TODO::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->guano, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
						this->complete();
					},
					Voices::GetNextVoiceShort(),
					true
				));
			}
			else
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::TODO::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->scrappy, false),
						DialogueEvents::BuildPreviewNode(&this->scaldor, true)
					),
					[=]()
					{
					},
					Voices::GetNextVoiceMedium(),
					false
				));
			}
		});
	});
}