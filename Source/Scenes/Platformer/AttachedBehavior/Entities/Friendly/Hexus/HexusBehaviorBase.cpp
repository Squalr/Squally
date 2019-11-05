#include "HexusBehaviorBase.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/NotificationEvents.h"
#include "Events/HexusEvents.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Hexus/Hexus.h"
#include "Strings/Platformer/Entities/HowAboutARoundOfHexus.h"
#include "Strings/Platformer/Notifications/ItemWon.h"

using namespace cocos2d;

HexusBehaviorBase::HexusBehaviorBase(GameObject* owner, LocalizedString* dialogueChoiceOverride) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->dialogueChoiceOverride = dialogueChoiceOverride;
	this->rewardPool = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	if (this->dialogueChoiceOverride != nullptr)
	{
		this->addChild(this->dialogueChoiceOverride);
	}
}

HexusBehaviorBase::~HexusBehaviorBase()
{
}

void HexusBehaviorBase::onLoad()
{
	this->rewardPool = this->generateReward();

	if (this->rewardPool != nullptr)
	{
		this->addChild(this->rewardPool);
	}

	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		if (this->dialogueChoiceOverride != nullptr)
		{
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				this->dialogueChoiceOverride->clone(),
				[=]()
				{
					HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
				}),
				0.5f
			);
		}
		else
		{
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				Strings::Platformer_Entities_HowAboutARoundOfHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
				[=]()
				{
					HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
				}),
				0.5f
			);
		}
	});
}

void HexusBehaviorBase::onWin()
{
	if (!this->entity->getObjectStateOrDefault(this->getWinLossSaveKey(), Value(false)).asBool())
	{
		if (this->rewardPool != nullptr)
		{
			std::vector<Item*> items = this->rewardPool->getItems();

			for (auto it = items.begin(); it != items.end(); it++)
			{
				Inventory* playerInventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);

				NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(Strings::Platformer_Notifications_ItemWon::create(), (*it)->getString(), (*it)->getIconResource()));

				playerInventory->forceInsert(*it);	
			}
		}

		this->entity->saveObjectState(this->getWinLossSaveKey(), Value(true));
	}
}

void HexusBehaviorBase::onLoss()
{
}

void HexusBehaviorBase::onDraw()
{
}

HexusOpponentData* HexusBehaviorBase::createOpponentData()
{
    return HexusOpponentData::create( 
        // TODO: This needs to work similar to the dialogue boxes, and pass the entity to a builder that accounts for scale/offsets
        this->entity->getAnimations()->getAnimationResource(),
        this->getBackgroundResource(),
        this->entity->getScale(), // DEPRECATED
		Vec2::ZERO, // DEPRECATED
        Vec2::ZERO, // DEPRECATED
        this->entity->getDialogueOffset(),
        this->getWinLossSaveKey(),
        HexusOpponentData::Strategy::Random,
        Card::CardStyle::Light,
        0.0f, // DEPRECATED
        this->generateDeck(),
        [=](HexusOpponentData::Result result)
        {
			switch(result)
			{
				case HexusOpponentData::Result::Win:
				default:
				{
                	this->onWin();
					break;
				}
				case HexusOpponentData::Result::Loss:
				{
                	this->onLoss();
					break;
				}
				case HexusOpponentData::Result::Draw:
				{
                	this->onDraw();
					break;
				}
			}
        }
	);
}
