#include "BurchBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/DropPools/EndianForest/RewardPoolLycan.h"
#include "Objects/Platformer/Interactables/Chests/ChestBase.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BurchBehavior::MapKey = "burch";
const std::string BurchBehavior::SaveKeyAskedPermission = "ASKED_CHEST_PERMISSION";

BurchBehavior* BurchBehavior::create(GameObject* owner)
{
	BurchBehavior* instance = new BurchBehavior(owner);

	instance->autorelease();

	return instance;
}

BurchBehavior::BurchBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

BurchBehavior::~BurchBehavior()
{
}

void BurchBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<ChestBase>(this, [=](ChestBase* chest)
	{
		this->chest = chest;
		
		this->owner->listenForMapEventOnce("chest-opened", [=](ValueMap)
		{
			this->refreshPreText();
		});
	});
}

void BurchBehavior::onDisable()
{
	super::onDisable();
}

void BurchBehavior::refreshPreText()
{
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		if (this->dialogueOption != nullptr)
		{
			interactionBehavior->getMainDialogueSet()->removeDialogueOption(this->dialogueOption);
			this->dialogueOption = nullptr;
		}

		if (this->chest->isOpen())
		{
			if (!this->entity->loadObjectStateOrDefault(BurchBehavior::SaveKeyAskedPermission, Value(false)).asBool())
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_DataMines_Misc_Burch_C_Entitled::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->entity, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
					},
					Voices::GetNextVoiceShort(),
					false
				));
			}
		}
		else if (!this->entity->loadObjectStateOrDefault(BurchBehavior::SaveKeyAskedPermission, Value(false)).asBool())
		{
			this->dialogueOption = DialogueOption::create(
				Strings::Platformer_Quests_DataMines_Misc_Burch_A_CanWeTakeChestItems::create(),
				[=]()
				{
					DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_DataMines_Misc_Burch_B_Absolutely::create(),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Bottom,
							DialogueBox::DialogueAlignment::Right,
							DialogueEvents::BuildPreviewNode(&this->squally, false),
							DialogueEvents::BuildPreviewNode(&this->entity, true)
						),
						[=]()
						{
							this->entity->saveObjectState(BurchBehavior::SaveKeyAskedPermission, Value(true));
						},
						Voices::GetNextVoiceLong(),
						true
					));
				}),

			interactionBehavior->getMainDialogueSet()->addDialogueOption(this->dialogueOption, 1.0f);
		}
	});
}
