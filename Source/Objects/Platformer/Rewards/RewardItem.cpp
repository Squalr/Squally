#include "RewardItem.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Inventory/ItemMenu/ItemPreview.h"
#include "Objects/Platformer/Rewards/RewardPool.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RewardItem::MapKey = "reward-item";
const std::string RewardItem::PropertyRewardPool = "pool";

RewardItem* RewardItem::create(ValueMap& properties)
{
	RewardItem* instance = new RewardItem(properties);

	instance->autorelease();

	return instance;
}

RewardItem::RewardItem(ValueMap& properties) : super(properties)
{
	this->item = nullptr;
	this->itemPreview = ItemPreview::create(true, false);
	this->itemNode = Node::create();
	this->itemClickHitbox = ClickableNode::create();
	this->poolName = GameUtils::getKeyOrDefault(this->properties, RewardItem::PropertyRewardPool, Value("")).asString();
	this->available = true;

	this->setVisible(false);

	this->addChild(this->itemPreview);
	this->addChild(this->itemNode);
	this->addChild(this->itemClickHitbox);
}

RewardItem::~RewardItem()
{
}

void RewardItem::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
	
	ObjectEvents::WatchForObject<RewardPool>(this, [=](RewardPool* shopPool)
	{
		this->item = shopPool->getNextItem();

		if (this->item != nullptr)
		{
			this->setVisible(true);
			this->itemNode->addChild(this->item);
			this->itemPreview->preview(ItemPreview::EquipHintMode::None, this->item);
			this->itemPreview->toggleShowItemName(dynamic_cast<HexusCard*>(this->item) == nullptr);
		}
		else
		{
			this->setVisible(false);
		}
	}, this->poolName);
}

void RewardItem::initializePositions()
{
	super::initializePositions();
}

void RewardItem::initializeListeners()
{
	super::initializeListeners();

	this->itemClickHitbox->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->item == nullptr)
		{
			return;
		}

		NotificationEvents::TriggerConfirmation(NotificationEvents::ConfirmationArgs(
			Strings::Platformer_Dialogue_Rewards_DoYouWantThisReward::create()
				->setStringReplacementVariables(this->item->getString()),
			[=]()
			{
				this->sellItem();
				
				return false;
			},
			[=]()
			{
				return false;
			}
		));
	});
}

void RewardItem::sellItem()
{
	if (!this->available)
	{
		return;
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			PlatformerEvents::TriggerGiveItem(PlatformerEvents::GiveItemArgs(this->item->clone()));
			this->removeRewardItem();
		});
	}, Squally::MapKey);
}

void RewardItem::removeRewardItem()
{
	this->available = false;
	this->itemPreview->preview(ItemPreview::EquipHintMode::None, nullptr);
	this->itemClickHitbox->setMouseClickCallback(nullptr);
	this->itemClickHitbox->disableInteraction(0);
}
