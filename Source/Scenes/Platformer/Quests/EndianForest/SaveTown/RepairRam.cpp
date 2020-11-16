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
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Ram/Ram.h"
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

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
	this->impactSound = Sound::create(SoundResources::Platformer_Objects_Misc_BowlingStrike1);
	this->rollSound = WorldSound::create(SoundResources::Platformer_Objects_Machines_RollLoop1);
	this->wasActivated = false;

	this->addChild(this->repairInteract);
	this->addChild(this->impactSound);
	this->addChild(this->rollSound);
}

RepairRam::~RepairRam()
{
}

void RepairRam::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;

		this->squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
		});
	}, Squally::MapKey);
	
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Ram>(this, [=](Ram* ram)
	{
		this->ram = ram;

		if (questState == QuestState::Complete)
		{
			this->ram->setVisible(false);
			this->repairInteract->disable();
		}
		else
		{
			this->defer([=]()
			{
				this->wheel1 = this->ram->getAnimations()->getAnimationPart("wheel_1");
				this->wheel2 = this->ram->getAnimations()->getAnimationPart("wheel_2");
				this->wheel3 = this->ram->getAnimations()->getAnimationPart("wheel_3");

				this->refreshWheels();
			});
		}
	}, Ram::MapKey);

	this->repairInteract->setInteractCallback([=]()
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
	Objectives::SetCurrentObjective(ObjectiveKeys::EFConfrontCommander);
}

void RepairRam::onSkipped()
{
}

void RepairRam::runDialogue()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_SaveTown_Scrappy_A_RepairRam::create(),
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

void RepairRam::onRamInteract()
{
	if (this->inventory == nullptr || this->wasActivated)
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
	else if (wheelFoundCount < 3)
	{
		this->runDialogue();
	}

	this->refreshWheels();

	if (wheelFoundCount >= 3)
	{
		this->runAction(Sequence::create(
			DelayTime::create(1.5f),
			CallFunc::create([=]()
			{
				this->rollSound->play(true);
				this->ram->getCollision()->setAccelerationX(-12800.0f);
				this->ram->getAnimations()->clearAnimationPriority();
				this->ram->getAnimations()->playAnimation("Run", SmartAnimationNode::AnimationPlayMode::Repeat);
			}),
			DelayTime::create(2.5f),
			CallFunc::create([=]()
			{
				this->rollSound->stopAndFadeOut();

				// Disabled -- play on the next scene instead
				// this->impactSound->play();
			}),
			nullptr
		));

		this->wasActivated = true;

		this->complete();
	}
	else
	{
		Objectives::SetCurrentObjective(ObjectiveKeys::EFRepairRam);
	}
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
}
