#include "ItemMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Inventory/ItemMenu/ItemEntry.h"
#include "Menus/Inventory/ItemMenu/ItemPreview.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;


const cocos2d::Vec2 ItemMenu::DefaultPreviewOffset = Vec2(360.0f, 96.0f);
const cocos2d::Vec3 ItemMenu::DefaultTextOffset = Vec3(16.0f, 6.0f, 128.0f);
const float ItemMenu::LabelSpacing = 96.0f;
const Size ItemMenu::LabelSize = Size(288.0f, 32.0f);

ItemMenu* ItemMenu::create()
{
	ItemMenu* instance = new ItemMenu();

	instance->autorelease();

	return instance;
}

ItemMenu::ItemMenu()
{
	this->isFocused = false;
	this->itemEntryMapping = std::map<Item*, ItemEntry*>();
	this->visibleItems = std::vector<ItemEntry*>();
	this->currencyInventory = CurrencyInventory::create(SaveKeys::SaveKeySquallyCurrencyInventory);
	this->equipmentInventory = EquipmentInventory::create(SaveKeys::SaveKeySquallyEquipment);
	this->inventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);
	this->itemPreview = ItemPreview::create();
	this->selectedInventoryRow = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectActive);
	this->itemListNodeContent = Node::create();
	this->itemListNode = SmartClippingNode::create(this->itemListNodeContent, Rect(Vec2(-160.0f, -304.0f), Size(320.0f, 608.0f)));
	this->inventorySelectionArrow = Sprite::create(UIResources::Menus_InventoryMenu_Arrow);
	this->previewOffset = ItemMenu::DefaultPreviewOffset;
	this->textOffset = ItemMenu::DefaultTextOffset;
	this->selectedItemIndex = 0;
	
	this->addChild(this->currencyInventory);
	this->addChild(this->equipmentInventory);
	this->addChild(this->inventory);
	this->addChild(this->selectedInventoryRow);
	this->addChild(this->itemListNode);
	this->addChild(this->inventorySelectionArrow);
	this->addChild(this->itemPreview);
}

ItemMenu::~ItemMenu()
{
}

void ItemMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	this->unfocus();
	this->selectedItemIndex = 0;
}

void ItemMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->itemListNode->setPosition(Vec2(-340.0f + 342.0f, 0.0f));
	this->inventorySelectionArrow->setPosition(Vec2(-186.0f, 0.0f));
	this->selectedInventoryRow->setPosition(Vec2(0.0f, 0.0f));
	this->itemPreview->setPosition(this->previewOffset);
}

void ItemMenu::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		if (!this->isFocused || this->visibleItems.empty())
		{
			return;
		}

		ItemEntry* entry = this->visibleItems[this->selectedItemIndex];

		if (entry->getToggleCallback() != nullptr)
		{
			entry->getToggleCallback()();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->scrollInventoryUp();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->scrollInventoryDown();
	});
}

void ItemMenu::clearPreview()
{
	this->itemPreview->preview(nullptr);
}

void ItemMenu::clearVisibleItems()
{
	for (auto it = this->itemEntryMapping.begin(); it != itemEntryMapping.end(); it++)
	{
		(*it).second->setVisible(false);
	}

	this->visibleItems.clear();
}

ItemEntry* ItemMenu::pushVisibleItem(Item* visibleItem, std::function<void()> onToggle)
{
	ItemEntry* itemEntry = nullptr;

	for (auto entry : this->visibleItems)
	{
		if (entry->getAssociatedItem()->getItemName() == visibleItem->getItemName())
		{
			if (entry->getStackSize() < entry->getAssociatedItem()->getStackSize())
			{
				entry->setStackSize(entry->getStackSize() + 1);

				return entry;
			}
		}
	}

	if (this->itemEntryMapping.find(visibleItem) == this->itemEntryMapping.end())
	{
		
		if (dynamic_cast<HexusCard*>(visibleItem) != nullptr)
		{
			itemEntry = ItemEntry::create(visibleItem, visibleItem->getString(), UIResources::Menus_InventoryMenu_HexusIcon);
		}
		else if (dynamic_cast<Equipable*>(visibleItem) != nullptr)
		{
			itemEntry = ItemEntry::create(visibleItem, visibleItem->getString(), UIResources::Menus_InventoryMenu_EquippedIcon);
		}
		else
		{
			itemEntry = ItemEntry::create(visibleItem, visibleItem->getString());
		}

		this->itemEntryMapping[visibleItem] = itemEntry;
		this->itemListNodeContent->addChild(itemEntry);
	}
	else
	{
		itemEntry = this->itemEntryMapping[visibleItem];
	}

	this->visibleItems.push_back(itemEntry);
	itemEntry->setVisible(true);
	itemEntry->setToggleCallback(onToggle);

	return itemEntry;
}

void ItemMenu::focus()
{
	this->isFocused = true;
	this->inventorySelectionArrow->setVisible(true);
	this->selectedInventoryRow->setVisible(true);

	this->updateAndPositionItemText();
}

void ItemMenu::unfocus()
{
	this->isFocused = false;
	this->inventorySelectionArrow->setVisible(false);
	this->selectedInventoryRow->setVisible(false);
	this->clearPreview();
	
	this->updateAndPositionItemText();
}

void ItemMenu::scrollInventoryUp()
{
	if (!this->isFocused)
	{
		return;
	}

	this->selectedItemIndex = MathUtils::clamp(this->selectedItemIndex - 1, 0, this->visibleItems.size() - 1);

	this->updateAndPositionItemText();
}

void ItemMenu::scrollInventoryDown()
{
	if (!this->isFocused)
	{
		return;
	}
	
	this->selectedItemIndex = MathUtils::clamp(this->selectedItemIndex + 1, 0, this->visibleItems.size() - 1);

	this->updateAndPositionItemText();
}

void ItemMenu::setPreviewOffset(Vec2 previewOffset)
{
	this->previewOffset = previewOffset;

	this->itemPreview->setPosition(this->previewOffset);
}

void ItemMenu::setTextOffset(Vec3 textOffset)
{
	this->textOffset = textOffset;

	this->updateAndPositionItemText();
}

void ItemMenu::updateAndPositionItemText()
{
	if (this->visibleItems.empty())
	{
		return;
	}

	int adjustedIndex = this->selectedItemIndex - this->visibleItems.size() / 2;
	float offset = float(adjustedIndex) * ItemMenu::LabelSpacing;

	this->itemListNodeContent->setPositionY(offset);

	const float OffsetY = ItemMenu::LabelSpacing * float(this->visibleItems.size() / 2);
	int index = 0;

	for (auto it = this->visibleItems.begin(); it != this->visibleItems.end(); it++, index++)
	{
		(*it)->setPositionX(0.0f);
		(*it)->setPositionY(float(index) * -ItemMenu::LabelSpacing + OffsetY);
		(*it)->setPositionZ(0.0f);
	}
	
	if (this->isFocused)
	{
		this->itemPreview->preview(this->visibleItems[this->selectedItemIndex]->getAssociatedItem());
	}
	
	this->visibleItems[this->selectedItemIndex]->setPositionX(this->textOffset.x);
	this->visibleItems[this->selectedItemIndex]->setPositionY(this->visibleItems[this->selectedItemIndex]->getPositionY() + this->textOffset.y);
	this->visibleItems[this->selectedItemIndex]->setPositionZ(this->textOffset.z);
}
