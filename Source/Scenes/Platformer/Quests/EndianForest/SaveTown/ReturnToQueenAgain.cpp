#include "ReturnToQueenAgain.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/EndianForest/QueenLiana.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/DropPools/EndianForest/RewardPoolElriel.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToElriel.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReturnToQueenAgain::MapKeyQuest = "return-to-queen-again";

ReturnToQueenAgain* ReturnToQueenAgain::create(GameObject* owner, QuestLine* questLine)
{
	ReturnToQueenAgain* instance = new ReturnToQueenAgain(owner, questLine);

	instance->autorelease();

	return instance;
}

ReturnToQueenAgain::ReturnToQueenAgain(GameObject* owner, QuestLine* questLine) : super(owner, questLine, ReturnToQueenAgain::MapKeyQuest, false)
{
	ValueMap props = ValueMap();
	
	this->guano = nullptr;
	this->queenLiana = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->rewardPool = RewardPoolElriel::create(props);

	this->addChild(this->rewardPool);
}

ReturnToQueenAgain::~ReturnToQueenAgain()
{
}

void ReturnToQueenAgain::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<QueenLiana>(this, [=](QueenLiana* queenLiana)
	{
		this->queenLiana = queenLiana;
	}, QueenLiana::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void ReturnToQueenAgain::onActivate(bool isActiveThroughSkippable)
{
	this->runCinematicSequence();
}

void ReturnToQueenAgain::onComplete()
{
	PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(this->rewardPool));
}

void ReturnToQueenAgain::onSkipped()
{
	this->removeAllListeners();
}

void ReturnToQueenAgain::runCinematicSequence()
{
	if (this->queenLiana == nullptr)
	{
		return;
	}
	
	this->queenLiana->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_SaveTown_Return_A_CanWeLeave::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->queenLiana, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterQuestion1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_SaveTown_Return_B_Yes::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->queenLiana, true)
			),
			[=]()
			{
				this->complete();
			},
			SoundResources::Platformer_Entities_Generic_ChatterShort2,
			true
		));
	});
}
