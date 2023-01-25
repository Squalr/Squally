#include "RezLazarus.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Lazarus.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Warp.h"
#include "Objects/Platformer/Interactables/Ram/Ram.h"
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RezLazarus::MapKeyQuest = "rez-lazarus";
const std::string RezLazarus::TurnedInGemCount = "SAVE_KEY_GEM_TURNED_IN_COUNT";
const std::string RezLazarus::GemTurnedInRed = "SAVE_KEY_GEM_TURNED_IN_RED";
const std::string RezLazarus::GemTurnedInPurple = "SAVE_KEY_GEM_TURNED_IN_PURPLE";
const std::string RezLazarus::GemTurnedInBlue = "SAVE_KEY_GEM_TURNED_IN_BLUE";

RezLazarus* RezLazarus::create(GameObject* owner, QuestLine* questLine)
{
	RezLazarus* instance = new RezLazarus(owner, questLine);

	instance->autorelease();

	return instance;
}

RezLazarus::RezLazarus(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RezLazarus::MapKeyQuest, false)
{
	this->repairInteract = InteractObject::create(InteractObject::InteractType::Input, CSize(512.0f, 288.0f));

	this->addChild(this->repairInteract);
}

RezLazarus::~RezLazarus()
{
}

void RezLazarus::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;

		this->squally->watchForComponent<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
		});
	}, Squally::MapKey);
	
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);
	
	ObjectEvents::WatchForObject<Warp>(this, [=](Warp* warp)
	{
		if (questState != QuestState::Complete)
		{
			warp->disable();
			this->lazarusWarps.push_back(warp);
		}
	}, "lazarus-portal-a");
	
	ObjectEvents::WatchForObject<Warp>(this, [=](Warp* warp)
	{
		if (questState != QuestState::Complete)
		{
			warp->disable();
			this->lazarusWarps.push_back(warp);
		}
	}, "lazarus-portal-b");
	
	ObjectEvents::WatchForObject<Lazarus>(this, [=](Lazarus* lazarus)
	{
		this->lazarus = lazarus;

		if (questState != QuestState::Complete)
		{
			this->lazarus->setOpacity(0);
		}
	}, Lazarus::MapKey);
	
	ObjectEvents::WatchForObject<GameObject>(this, [=](GameObject* displayGemRed)
	{
		this->displayGemRed = displayGemRed;
	}, "gem-red");
	
	ObjectEvents::WatchForObject<GameObject>(this, [=](GameObject* displayGemPurple)
	{
		this->displayGemPurple = displayGemPurple;
	}, "gem-purple");
	
	ObjectEvents::WatchForObject<GameObject>(this, [=](GameObject* displayGemBlue)
	{
		this->displayGemBlue = displayGemBlue;
	}, "gem-blue");

	this->defer([=]()
	{
		this->refreshGems();
	}, 2);

	if (questState != QuestState::Complete)
	{
		this->repairInteract->setInteractCallback([=]()
		{
			this->onRamInteract();

			return true;
		});
	}
	else
	{
		this->repairInteract->disable();
	}
}

void RezLazarus::onActivate(bool isActiveThroughSkippable)
{
}

void RezLazarus::onComplete()
{
	for (Warp* warp : this->lazarusWarps)
	{
		warp->enable();
	}

	if (this->repairInteract != nullptr)
	{
		this->repairInteract->disable();
	}
}

void RezLazarus::onSkipped()
{
}

void RezLazarus::runDialogue()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		true
	));
}

void RezLazarus::onRamInteract()
{
	if (this->inventory == nullptr || this->wasActivated)
	{
		return;
	}

	Key* redGem = this->inventory->getItemOfType<MayanGemRedItem>();
	Key* blueGem = this->inventory->getItemOfType<MayanGemBlueItem>();
	Key* purpleGem = this->inventory->getItemOfType<MayanGemPurpleItem>();

	int turnedInGemCountOriginal = this->getQuestSaveStateOrDefault(RezLazarus::TurnedInGemCount, Value(0)).asInt();
	int turnedInGemCount = turnedInGemCountOriginal;

	Objectives::SetCurrentObjective(ObjectiveKeys::LCFindGems);
	
	if (redGem != nullptr)
	{
		PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(redGem));
		inventory->tryRemove(redGem);
		turnedInGemCount++;
		this->saveQuestSaveState(RezLazarus::GemTurnedInRed, Value(true));
	}
	if (blueGem != nullptr)
	{
		PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(blueGem));
		inventory->tryRemove(blueGem);
		turnedInGemCount++;
		this->saveQuestSaveState(RezLazarus::GemTurnedInBlue, Value(true));
	}
	if (purpleGem != nullptr)
	{
		PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(purpleGem));
		inventory->tryRemove(purpleGem);
		turnedInGemCount++;
		this->saveQuestSaveState(RezLazarus::GemTurnedInPurple, Value(true));
	}

	if (turnedInGemCount != turnedInGemCountOriginal)
	{
		this->saveQuestSaveState(RezLazarus::TurnedInGemCount, Value(turnedInGemCount));
		this->refreshGems();
	}
	
	if (turnedInGemCount < 3)
	{
		this->runDialogue();

		if (turnedInGemCount != turnedInGemCountOriginal)
		{
			return;
		}
	}
	else
	{
		this->wasActivated = true;
		this->complete();
	}
}

void RezLazarus::refreshGems()
{
	bool redGemFound = this->getQuestSaveStateOrDefault(RezLazarus::GemTurnedInRed, Value(false)).asBool();
	bool blueGemFound = this->getQuestSaveStateOrDefault(RezLazarus::GemTurnedInBlue, Value(false)).asBool();
	bool purpleGemFound = this->getQuestSaveStateOrDefault(RezLazarus::GemTurnedInPurple, Value(false)).asBool();

	if (this->displayGemRed != nullptr)
	{
		this->displayGemRed->runAction(FadeTo::create(redGemFound ? 0.5f : 0.0f, redGemFound ? 255 : 0));
	}

	if (this->displayGemBlue != nullptr)
	{
		this->displayGemBlue->runAction(FadeTo::create(blueGemFound ? 0.5f : 0.0f, blueGemFound ? 255 : 0));
	}

	if (this->displayGemPurple != nullptr)
	{
		this->displayGemPurple->runAction(FadeTo::create(purpleGemFound ? 0.5f : 0.0f, purpleGemFound ? 255 : 0));
	}
}

void RezLazarus::runCinematicSequence()
{
}
