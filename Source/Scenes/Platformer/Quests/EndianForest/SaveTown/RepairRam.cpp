#include "RepairRam.h"

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
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Ram/Ram.h"
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RepairRam::MapKeyQuest = "repair-ram";
const std::string RepairRam::WheelFoundCount = "SAVE_KEY_WHEELS_FOUND";

RepairRam* RepairRam::create(GameObject* owner, QuestLine* questLine)
{
	RepairRam* instance = new RepairRam(owner, questLine);

	instance->autorelease();

	return instance;
}

RepairRam::RepairRam(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RepairRam::MapKeyQuest, false)
{
	this->ram = nullptr;
	this->wheel1 = nullptr;
	this->wheel2 = nullptr;
	this->wheel3 = nullptr;
	this->inventory = nullptr;
	this->repairInteract = InteractObject::create(InteractObject::InteractType::Input, Size(512.0f, 288.0f));

	this->addChild(this->repairInteract);
}

RepairRam::~RepairRam()
{
}

void RepairRam::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
		});
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<Ram>(this, [=](Ram* ram)
	{
		this->ram = ram;

		this->defer([=]()
		{
			this->wheel1 = this->ram->getAnimations()->getAnimationPart("wheel_1");
			this->wheel2 = this->ram->getAnimations()->getAnimationPart("wheel_2");
			this->wheel3 = this->ram->getAnimations()->getAnimationPart("wheel_3");

			this->refreshWheels();
		});
	}, Ram::MapKeyRam);

	this->repairInteract->setOpenCallback([=]()
	{
		this->onRamInteract();

		return true;
	});
}

void RepairRam::onActivate(bool isActiveThroughSkippable)
{
}

void RepairRam::onComplete()
{
	/*
	SaveManager::SaveProfileData(SaveKeys::SaveKeyBlessingOfWind, Value(true));
	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
	
	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Platformer_Blessings_BlessingGranted::create(),
		Strings::Platformer_Blessings_BlessingOfWind::create(),
		ObjectResources::Items_Misc_EssenceOfWind,
		SoundResources::Notifications_NotificationGood1
	));
	*/
}

void RepairRam::onSkipped()
{
}

void RepairRam::onRamInteract()
{
	if (this->inventory == nullptr)
	{
		return;
	}

	std::vector<RamWheel*> ramWheels = this->inventory->getItemsOfType<RamWheel>();
	int wheelFoundCount = this->getQuestSaveStateOrDefault(RepairRam::WheelFoundCount, Value(0)).asInt();
	
	if (!ramWheels.empty())
	{
		PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(ramWheels.back()));

		for (auto next : ramWheels)
		{
			inventory->tryRemove(next);
		}

		wheelFoundCount += ramWheels.size();
		this->saveQuestSaveState(RepairRam::WheelFoundCount, Value(wheelFoundCount));
	}

	this->refreshWheels();
}

void RepairRam::refreshWheels()
{
	int wheelFoundCount = this->getQuestSaveStateOrDefault(RepairRam::WheelFoundCount, Value(0)).asInt();
	bool wheel1Found = wheelFoundCount >= 1;
	bool wheel2Found = wheelFoundCount >= 2;
	bool wheel3Found = wheelFoundCount >= 3;

	if (this->wheel1 != nullptr)
	{
		if (wheel1Found)
		{
			this->wheel1->restoreSprite();
		}
		else
		{
			this->wheel1->replaceSprite(UIResources::EmptyImage);
		}
	}

	if (this->wheel2 != nullptr)
	{
		if (wheel2Found)
		{
			this->wheel2->restoreSprite();
		}
		else
		{
			this->wheel2->replaceSprite(UIResources::EmptyImage);
		}
	}

	if (this->wheel3 != nullptr)
	{
		if (wheel3Found)
		{
			this->wheel3->restoreSprite();
		}
		else
		{
			this->wheel3->replaceSprite(UIResources::EmptyImage);
		}
	}
}

void RepairRam::runCinematicSequence()
{
	/*
	if (this->sarude == nullptr)
	{
		return;
	}

	this->sarude->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_RepairRam_Marcel_A_GoodUse::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterQuestion1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_RepairRam_Marcel_B_Latent::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				this->complete();
			},
			SoundResources::Platformer_Entities_Generic_ChatterQuestion1,
			true
		));
	});
	*/
}
