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
#include "Menus/Inventory/ItemMenu/ItemPreview.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Return.h"

using namespace cocos2d;

const float ItemMenu::LabelSpacing = 96.0f;
const Size ItemMenu::LabelSize = Size(288.0f, 32.0f);
const int ItemMenu::MinHexusCards = 20;

ItemMenu* ItemMenu::create()
{
	ItemMenu* instance = new ItemMenu();

	instance->autorelease();

	return instance;
}

ItemMenu::ItemMenu()
{
	this->isFocused = false;
	this->currencyInventory = CurrencyInventory::create(SaveKeys::SaveKeySquallyCurrencyInventory);
	this->equipmentInventory = EquipmentInventory::create(SaveKeys::SaveKeySquallyEquipment);
	this->inventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);
	this->itemPreview = ItemPreview::create();
	this->selectedInventoryRow = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectActive);
	this->itemListNodeContent = Node::create();
	this->itemListNode = SmartClippingNode::create(this->itemListNodeContent, Rect(Vec2(-160.0f, -304.0f), Size(320.0f, 608.0f)));
	this->inventorySelectionArrow = Sprite::create(UIResources::Menus_InventoryMenu_Arrow);
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
	this->itemPreview->setPosition(Vec2(360.0f, 96.0f));
}

void ItemMenu::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		this->toggleEquipSelectedItem();
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

void ItemMenu::setVisibleItems(std::vector<Item*> visibleItems)
{
	this->visibleItems = visibleItems;
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

	this->updateAndPositionItemText();
}

void ItemMenu::scrollInventoryUp()
{
	this->selectedItemIndex = MathUtils::wrappingNormalize(this->selectedItemIndex - 1, 0, this->visibleItems.size() - 1);

	this->updateAndPositionItemText();
}

void ItemMenu::scrollInventoryDown()
{
	this->selectedItemIndex = MathUtils::wrappingNormalize(this->selectedItemIndex + 1, 0, this->visibleItems.size() - 1);

	this->updateAndPositionItemText();
}

void ItemMenu::buildInventoryList()
{
	this->itemListNodeContent->removeAllChildren();

	this->updateAndPositionItemText();
}

void ItemMenu::updateAndPositionItemText()
{
	// this->visibleInventoryItems.clear();
	// this->visibleEquippedItems.clear();
	std::vector<Node*> visibleItemLabels = std::vector<Node*>();

	int index = 0;

	/*
	switch(this->activeFilter)
	{
		case ActiveFilter::All:
		case ActiveFilter::Equipment:
		{
			for (auto it = this->equippedItems.begin(); it != this->equippedItems.end(); it++, index++)
			{
				// Exclude hexus cards from the "all/equip" menu
				if (dynamic_cast<HexusCard*>(*it) == nullptr)
				{
					this->visibleEquippedItems.push_back(*it);
					visibleItemLabels.push_back(this->equippedItemLabels[index]);
				}
			}

			break;
		}
		case ActiveFilter::Hexus:
		{
			for (auto it = this->equippedItems.begin(); it != this->equippedItems.end(); it++, index++)
			{
				// Only show equipped hexus cards
				if (dynamic_cast<HexusCard*>(*it) != nullptr)
				{
					this->visibleEquippedItems.push_back(*it);
					visibleItemLabels.push_back(this->equippedItemLabels[index]);
				}
			}

			break;
		}
		default:
		{
			break;
		}
	}

	index = 0;

	for (auto it = this->inventoryItems.begin(); it != this->inventoryItems.end(); it++, index++)
	{
		switch(this->activeFilter)
		{
			case ActiveFilter::All:
			{
				// Exclude hexus cards from the "all" menu
				if (dynamic_cast<HexusCard*>(*it) == nullptr)
				{
					this->visibleInventoryItems.push_back(*it);
					visibleItemLabels.push_back(this->itemLabels[index]);
				}

				break;
			}
			case ActiveFilter::Equipment:
			{
				// While cards are technically equipped, exclude them here
				if (dynamic_cast<Equipable*>(*it) != nullptr && dynamic_cast<HexusCard*>(*it) == nullptr)
				{
					this->visibleInventoryItems.push_back(*it);
					visibleItemLabels.push_back(this->itemLabels[index]);
				}

				break;
			}
			case ActiveFilter::Consumables:
			{
				if (dynamic_cast<Consumable*>(*it) != nullptr)
				{
					this->visibleInventoryItems.push_back(*it);
					visibleItemLabels.push_back(this->itemLabels[index]);
				}

				break;
			}
			case ActiveFilter::Crafting:
			{
				if (dynamic_cast<Consumable*>(*it) != nullptr)
				{
					this->visibleInventoryItems.push_back(*it);
					visibleItemLabels.push_back(this->itemLabels[index]);
				}

				break;
			}
			case ActiveFilter::Hexus:
			{
				if (dynamic_cast<HexusCard*>(*it) != nullptr)
				{
					this->visibleInventoryItems.push_back(*it);
					visibleItemLabels.push_back(this->itemLabels[index]);
				}

				break;
			}
			case ActiveFilter::Misc:
			{
				if (dynamic_cast<Consumable*>(*it) != nullptr)
				{
					this->visibleInventoryItems.push_back(*it);
					visibleItemLabels.push_back(this->itemLabels[index]);
				}
				
				break;
			}
			default:
			{
				break;
			}
		}
	}

	for (auto it = this->equippedItemLabels.begin(); it != this->equippedItemLabels.end(); it++)
	{
		(*it)->setVisible(false);
		(*it)->setPositionX(0.0f);
		(*it)->setPositionY(0.0f);
		(*it)->setPositionZ(0.0f);
	}

	for (auto it = this->itemLabels.begin(); it != this->itemLabels.end(); it++)
	{
		(*it)->setVisible(false);
		(*it)->setPositionX(0.0f);
		(*it)->setPositionY(0.0f);
		(*it)->setPositionZ(0.0f);
	}
	
	this->selectedItemIndex = visibleItemLabels.size() <= 0 ? 0 : MathUtils::clamp(this->selectedItemIndex, 0, visibleItemLabels.size() - 1);
	int adjustedIndex = this->selectedItemIndex - visibleItemLabels.size() / 2;
	float offset = float(adjustedIndex) * ItemMenu::LabelSpacing;

	this->itemListNodeContent->setPositionY(offset);
	this->itemPreview->clearPreview();

	if (visibleItemLabels.empty())
	{
		return;
	}

	const float offsetY = ItemMenu::LabelSpacing * float(visibleItemLabels.size() / 2);
	index = 0;

	for (auto it = visibleItemLabels.begin(); it != visibleItemLabels.end(); it++, index++)
	{
		(*it)->setVisible(true);
		(*it)->setPositionY(float(index) * -ItemMenu::LabelSpacing + offsetY);
	}

	if (this->activeFocus == ActiveFocus::Inventory)
	{
		const float XOffset = 16.0f;
		const float YOffset = 6.0f;
		const float ZOffset = 128.0f;

		visibleItemLabels[this->selectedItemIndex]->setPositionX(XOffset);
		visibleItemLabels[this->selectedItemIndex]->setPositionY(visibleItemLabels[this->selectedItemIndex]->getPositionY() + YOffset);
		visibleItemLabels[this->selectedItemIndex]->setPositionZ(ZOffset);

		this->itemPreview->preview(this->visibleInventoryItems[this->selectedItemIndex]);
	}
	*/
}

void ItemMenu::toggleEquipSelectedItem()
{
	/*
	if (this->activeFocus != ActiveFocus::Inventory)
	{
		return;
	}
	
	bool isSelectionInEquipment = this->selectedItemIndex < this->visibleEquippedItems.size();

	if (isSelectionInEquipment)
	{
		Item* selectedItem = this->visibleEquippedItems[this->selectedItemIndex];
		
		// Check if it's even an equipable item...
		if (dynamic_cast<HexusCard*>(selectedItem) != nullptr)
		{
			if (this->equipmentInventory->getHexusCards().size() <= ItemMenu::MinHexusCards)
			{
				return;
			}
		}
		
		this->equipmentInventory->tryTransact(this->inventory, selectedItem, nullptr, [=](Item* item, Item* otherItem)
		{
			// Success unequipping item -- visually best if this ends up in the 1st inventory slot
			this->inventory->moveItem(item, 0);
		},
		[=](Item* item, Item* otherItem)
		{
			// Failure
			LogUtils::logError("Error unequipping item!");

			if (otherItem != nullptr)
			{
				LogUtils::logError(otherItem->getName());
			}
		});
	
		this->buildInventoryList();
	}
	else
	{
		int adjustedIndex = this->selectedItemIndex - this->visibleEquippedItems.size();
		Item* selectedItem = this->visibleInventoryItems[adjustedIndex];
		Item* equippedItem = nullptr;
		std::string selectedItemName = selectedItem == nullptr ? "" : selectedItem->getName();
		
		// Check if it's even an equipable item...
		if (dynamic_cast<Equipable*>(selectedItem) == nullptr)
		{
			return;
		}

		if (dynamic_cast<Hat*>(selectedItem))
		{
			equippedItem = this->equipmentInventory->getHat();
		}
		else if (dynamic_cast<Weapon*>(selectedItem))
		{
			equippedItem = this->equipmentInventory->getWeapon();
		}
		else if (dynamic_cast<Offhand*>(selectedItem))
		{
			equippedItem = this->equipmentInventory->getOffhand();
		}
		
		this->inventory->tryTransact(this->equipmentInventory, selectedItem, equippedItem, [=](Item* item, Item* otherItem)
		{
			// Success equipping item. Adjust final position if equipping an item without a swap
			if (otherItem == nullptr)
			{
				this->equipmentInventory->moveItem(item, this->equipmentInventory->getItems().size());
			}
		},
		[=](Item* item, Item* otherItem)
		{
			// Failure
			LogUtils::logError("Error equipping item!");

			if (item != nullptr)
			{
				LogUtils::logError(item->getName());
			}

			if (otherItem != nullptr)
			{
				LogUtils::logError(otherItem->getName());
			}
		});
	
		this->buildInventoryList();
	}

	PlatformerEvents::TriggerEquippedItemsChanged();
	*/
}

cocos2d::Node* ItemMenu::buildMenuLabel(LocalizedString* text, Sprite* icon)
{
	Node* contentNode = Node::create();

	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);

	label->setAnchorPoint(Vec2(0.0f, 0.5f));
	label->enableOutline(Color4B::BLACK, 2);
	label->setPositionX(-ItemMenu::LabelSize.width / 2.0f);

	contentNode->addChild(label);

	if (icon != nullptr)
	{
		label->setPositionX(label->getPositionX() + 40.0f);
		contentNode->addChild(icon);

		icon->setPositionX(-ItemMenu::LabelSize.width / 2.0f + 16.0f);
	}

	return contentNode;
}
