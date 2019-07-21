#include "InventoryMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Inventory/PlayerEquipment.h"
#include "Scenes/Platformer/Inventory/PlayerInventory.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Inventory/All.h"
#include "Strings/Menus/Inventory/Consumables.h"
#include "Strings/Menus/Inventory/Crafting.h"
#include "Strings/Menus/Inventory/Equipment.h"
#include "Strings/Menus/Inventory/Inventory.h"
#include "Strings/Menus/Inventory/Misc.h"
#include "Strings/Menus/Return.h"

// DEBUG
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/SantaHat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/BlueAxe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/CandySword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/CrystalSword.h"

using namespace cocos2d;

const float InventoryMenu::LabelSpacing = 96.0f;
const Size InventoryMenu::LabelSize = Size(288.0f, 32.0f);

InventoryMenu* InventoryMenu::create()
{
	InventoryMenu* instance = new InventoryMenu();

	instance->autorelease();

	return instance;
}

InventoryMenu::InventoryMenu()
{
	this->inventoryWindow = Sprite::create(UIResources::Menus_InventoryMenu_InventoryMenu);
	this->equipmentPanel = Sprite::create(UIResources::Menus_InventoryMenu_EquipmentMenu);
	this->itemPreview = ItemPreview::create();
	this->contentNode = Node::create();
	this->selectedFilterRowActive = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectActive);
	this->selectedFilterRowInactive = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectInactive);
	this->selectedInventoryRow = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectActive);
	this->filterNodeContent = Node::create();
	this->filterNode = SmartClippingNode::create(this->filterNodeContent, Rect(Vec2(-160.0f, -304.0f), Size(320.0f, 608.0f)));
	this->inventoryNodeContent = Node::create();
	this->inventoryNode = SmartClippingNode::create(this->inventoryNodeContent, Rect(Vec2(-160.0f, -304.0f), Size(320.0f, 608.0f)));
	this->filterSelectionArrow = Sprite::create(UIResources::Menus_InventoryMenu_Arrow);
	this->inventorySelectionArrow = Sprite::create(UIResources::Menus_InventoryMenu_Arrow);
	this->closeButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->inventoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Inventory_Inventory::create());
	this->returnClickCallback = nullptr;
	this->activeFocus = ActiveFocus::Filter;
	this->activeFilter = ActiveFilter::All;
	this->selectedItemIndex = 0;
	this->filterLabels = std::vector<Node*>();
	this->itemLabels = std::vector<Node*>();
	this->equippedItems = std::vector<Item*>();
	this->equippedItemLabels = std::vector<Node*>();
	this->inventoryItems = std::vector<Item*>();

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->setTextColor(Color4B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->inventoryLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->inventoryLabel->enableGlow(Color4B::BLACK);

	this->allLabel = this->buildMenuLabel(Strings::Menus_Inventory_All::create(), Sprite::create(UIResources::Menus_InventoryMenu_AllIcon));
	this->equipmentLabel = this->buildMenuLabel(Strings::Menus_Inventory_Equipment::create(), Sprite::create(UIResources::Menus_InventoryMenu_EquipmentIcon));
	this->consumablesLabel = this->buildMenuLabel(Strings::Menus_Inventory_Consumables::create(), Sprite::create(UIResources::Menus_InventoryMenu_ConsumablesIcon));
	this->craftingLabel = this->buildMenuLabel(Strings::Menus_Inventory_Crafting::create(), Sprite::create(UIResources::Menus_InventoryMenu_CraftingIcon));
	this->miscLabel = this->buildMenuLabel(Strings::Menus_Inventory_Misc::create(), Sprite::create(UIResources::Menus_InventoryMenu_MiscIcon));

	this->filterLabels.push_back(this->allLabel);
	this->filterLabels.push_back(this->equipmentLabel);
	this->filterLabels.push_back(this->consumablesLabel);
	this->filterLabels.push_back(this->craftingLabel);
	this->filterLabels.push_back(this->miscLabel);
	
	this->filterNodeContent->addChild(this->allLabel);
	this->filterNodeContent->addChild(this->equipmentLabel);
	this->filterNodeContent->addChild(this->consumablesLabel);
	this->filterNodeContent->addChild(this->craftingLabel);
	this->filterNodeContent->addChild(this->miscLabel);
	this->contentNode->addChild(this->selectedFilterRowActive);
	this->contentNode->addChild(this->selectedFilterRowInactive);
	this->contentNode->addChild(this->selectedInventoryRow);
	this->contentNode->addChild(this->filterNode);
	this->contentNode->addChild(this->inventoryNode);
	this->contentNode->addChild(this->filterSelectionArrow);
	this->contentNode->addChild(this->inventorySelectionArrow);
	this->contentNode->addChild(this->itemPreview);
	this->addChild(this->inventoryWindow);
	this->addChild(this->equipmentPanel);
	this->addChild(this->contentNode);
	this->addChild(this->inventoryLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

InventoryMenu::~InventoryMenu()
{
}

void InventoryMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->inventoryWindow, delay, duration);
	GameUtils::fadeInObject(this->inventoryLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);

	// DEBUG
	PlayerInventory::getInstance()->forceInsert(SantaHat::create());
	PlayerInventory::getInstance()->forceInsert(BlueAxe::create());
	PlayerInventory::getInstance()->forceInsert(CandySword::create());
	PlayerInventory::getInstance()->forceInsert(HealthPotion::create());
	PlayerInventory::getInstance()->forceInsert(CrystalSword::create());
	this->equipmentPanel->setVisible(false);

	this->unfocusInventory();
	this->setActiveFilter(ActiveFilter::All);
	this->selectedItemIndex = 0;

	this->buildInventoryList();
}

void InventoryMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->inventoryWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->contentNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 44.0f));
	this->filterNode->setPosition(Vec2(-340.0f, 0.0f));
	this->inventoryNode->setPosition(Vec2(-340.0f + 342.0f, 0.0f));
	this->filterSelectionArrow->setPosition(Vec2(-524.0f, 0.0f));
	this->inventorySelectionArrow->setPosition(Vec2(-186.0f, 0.0f));
	this->selectedFilterRowActive->setPosition(Vec2(-341.0f, 0.0f));
	this->selectedFilterRowInactive->setPosition(Vec2(-341.0f, 0.0f));
	this->selectedInventoryRow->setPosition(Vec2(0.0f, 0.0f));
	this->itemPreview->setPosition(Vec2(360.0f, 96.0f));
	this->equipmentPanel->setPosition(Vec2(visibleSize.width / 2.0f + 292.0f, visibleSize.height / 2.0f + 64.0f));
	this->inventoryLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));

	const float offsetY = InventoryMenu::LabelSpacing * float(this->filterLabels.size() / 2);
	int index = 0;

	for (auto it = this->filterLabels.begin(); it != this->filterLabels.end(); it++, index++)
	{
		(*it)->setPositionY(float(index) * -InventoryMenu::LabelSpacing + offsetY);
	}
}

void InventoryMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handled = true;

		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		this->toggleEquipSelectedItem();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->focusInventory();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->unfocusInventory();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW }, [=](InputEvents::InputArgs* args)
	{
		switch(this->activeFocus)
		{
			case ActiveFocus::Filter:
			{
				this->scrollFilterUp();
				break;
			}
			case ActiveFocus::Inventory:
			{
				this->scrollInventoryUp();
				break;
			}
			default:
			{
				break;
			}
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW }, [=](InputEvents::InputArgs* args)
	{
		switch(this->activeFocus)
		{
			case ActiveFocus::Filter:
			{
				this->scrollFilterDown();
				break;
			}
			case ActiveFocus::Inventory:
			{
				this->scrollInventoryDown();
				break;
			}
			default:
			{
				break;
			}
		}
	});
}

void InventoryMenu::setReturnCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void InventoryMenu::setActiveFilter(ActiveFilter activeFilter)
{
	this->activeFilter = activeFilter;
	this->selectedItemIndex = 0;

	this->positionFilterText();
	this->updateAndPositionItemText();
}

void InventoryMenu::scrollFilterUp()
{
	switch(this->activeFilter)
	{
		case ActiveFilter::All:
		{
			// No looping
			this->setActiveFilter(ActiveFilter::All);
			break;
		}
		case ActiveFilter::Equipment:
		{
			this->setActiveFilter(ActiveFilter::All);
			break;
		}
		case ActiveFilter::Consumables:
		{
			this->setActiveFilter(ActiveFilter::Equipment);
			break;
		}
		case ActiveFilter::Crafting:
		{
			this->setActiveFilter(ActiveFilter::Consumables);
			break;
		}
		case ActiveFilter::Misc:
		{
			this->setActiveFilter(ActiveFilter::Crafting);
			break;
		}
		default:
		{
			break;
		}
	}

	this->positionFilterText();
}

void InventoryMenu::scrollFilterDown()
{
	switch(this->activeFilter)
	{
		case ActiveFilter::All:
		{
			this->setActiveFilter(ActiveFilter::Equipment);
			break;
		}
		case ActiveFilter::Equipment:
		{
			this->setActiveFilter(ActiveFilter::Consumables);
			break;
		}
		case ActiveFilter::Consumables:
		{
			this->setActiveFilter(ActiveFilter::Crafting);
			break;
		}
		case ActiveFilter::Crafting:
		{
			this->setActiveFilter(ActiveFilter::Misc);
			break;
		}
		case ActiveFilter::Misc:
		{
			// No looping
			this->setActiveFilter(ActiveFilter::Misc);
			break;
		}
		default:
		{
			break;
		}
	}

	this->positionFilterText();
}

void InventoryMenu::scrollInventoryUp()
{
	this->selectedItemIndex--;

	this->updateAndPositionItemText();
}

void InventoryMenu::scrollInventoryDown()
{
	this->selectedItemIndex++;

	this->updateAndPositionItemText();
}

void InventoryMenu::unfocusInventory()
{
	this->activeFocus = ActiveFocus::Filter;
	this->filterSelectionArrow->setVisible(true);
	this->inventorySelectionArrow->setVisible(false);
	this->selectedFilterRowActive->setVisible(true);
	this->selectedFilterRowInactive->setVisible(false);
	this->selectedInventoryRow->setVisible(false);

	this->updateAndPositionItemText();
}

void InventoryMenu::focusInventory()
{
	this->activeFocus = ActiveFocus::Inventory;
	this->filterSelectionArrow->setVisible(false);
	this->inventorySelectionArrow->setVisible(true);
	this->selectedFilterRowActive->setVisible(false);
	this->selectedFilterRowInactive->setVisible(true);
	this->selectedInventoryRow->setVisible(true);

	this->updateAndPositionItemText();
}

void InventoryMenu::buildInventoryList()
{
	this->inventoryNodeContent->removeAllChildren();
	this->equippedItemLabels.clear();
	this->itemLabels.clear();

	this->inventoryItems = PlayerInventory::getInstance()->getItems();
	this->equippedItems = PlayerEquipment::getInstance()->getItems();

	for (auto it = this->equippedItems.begin(); it != this->equippedItems.end(); it++)
	{
		Node* label = this->buildMenuLabel((*it)->getString(), Sprite::create(UIResources::Menus_InventoryMenu_EquippedIcon));

		this->equippedItemLabels.push_back(label);
		this->inventoryNodeContent->addChild(label);
	}

	for (auto it = this->inventoryItems.begin(); it != this->inventoryItems.end(); it++)
	{
		Node* label = this->buildMenuLabel((*it)->getString());

		this->itemLabels.push_back(label);
		this->inventoryNodeContent->addChild(label);
	}

	this->updateAndPositionItemText();
}

void InventoryMenu::positionFilterText()
{
	int adjustedIndex = (int)this->activeFilter - this->filterLabels.size() / 2;
	float offset = float(adjustedIndex) * InventoryMenu::LabelSpacing;

	this->filterNodeContent->setPositionY(offset);

	const float offsetY = InventoryMenu::LabelSpacing * float(this->filterLabels.size() / 2);
	int index = 0;

	for (auto it = this->filterLabels.begin(); it != this->filterLabels.end(); it++, index++)
	{
		(*it)->setPositionX(0.0f);
		(*it)->setPositionY(float(index) * -InventoryMenu::LabelSpacing + offsetY);
		(*it)->setPositionZ(0.0f);
	}

	const float XOffset = 64.0f;
	const float YOffset = 6.0f;
	const float ZOffset = 128.0f;

	switch(this->activeFilter)
	{
		case ActiveFilter::All:
		{
			this->allLabel->setPositionX(XOffset);
			this->allLabel->setPositionY(this->allLabel->getPositionY() + YOffset);
			this->allLabel->setPositionZ(ZOffset);
			break;
		}
		case ActiveFilter::Equipment:
		{
			this->equipmentLabel->setPositionX(XOffset);
			this->equipmentLabel->setPositionY(this->equipmentLabel->getPositionY() + YOffset);
			this->equipmentLabel->setPositionZ(ZOffset);
			break;
		}
		case ActiveFilter::Consumables:
		{
			this->consumablesLabel->setPositionX(XOffset);
			this->consumablesLabel->setPositionY(this->consumablesLabel->getPositionY() + YOffset);
			this->consumablesLabel->setPositionZ(ZOffset);
			break;
		}
		case ActiveFilter::Crafting:
		{
			this->craftingLabel->setPositionX(XOffset);
			this->craftingLabel->setPositionY(this->craftingLabel->getPositionY() + YOffset);
			this->craftingLabel->setPositionZ(ZOffset);
			break;
		}
		case ActiveFilter::Misc:
		{
			this->miscLabel->setPositionX(XOffset);
			this->miscLabel->setPositionY(this->miscLabel->getPositionY() + YOffset);
			this->miscLabel->setPositionZ(ZOffset);
			break;
		}
		default:
		{
			break;
		}
	}
}

void InventoryMenu::updateAndPositionItemText()
{
	std::vector<Item*> filteredItems = std::vector<Item*>();
	std::vector<Node*> filteredItemLabels = std::vector<Node*>();

	int index = 0;

	switch(this->activeFilter)
	{
		case ActiveFilter::All:
		case ActiveFilter::Equipment:
		{
			for (auto it = this->equippedItems.begin(); it != this->equippedItems.end(); it++, index++)
			{
				filteredItems.push_back(*it);
				filteredItemLabels.push_back(this->equippedItemLabels[index]);
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
				filteredItems.push_back(*it);
				filteredItemLabels.push_back(this->itemLabels[index]);
				break;
			}
			case ActiveFilter::Equipment:
			{
				if (dynamic_cast<Equipable*>(*it) != nullptr)
				{
					filteredItems.push_back(*it);
					filteredItemLabels.push_back(this->itemLabels[index]);
				}

				break;
			}
			case ActiveFilter::Consumables:
			{
				if (dynamic_cast<Consumable*>(*it) != nullptr)
				{
					filteredItems.push_back(*it);
					filteredItemLabels.push_back(this->itemLabels[index]);
				}

				break;
			}
			case ActiveFilter::Crafting:
			{
				if (dynamic_cast<Consumable*>(*it) != nullptr)
				{
					filteredItems.push_back(*it);
					filteredItemLabels.push_back(this->itemLabels[index]);
				}

				break;
			}
			case ActiveFilter::Misc:
			{
				if (dynamic_cast<Consumable*>(*it) != nullptr)
				{
					filteredItems.push_back(*it);
					filteredItemLabels.push_back(this->itemLabels[index]);
				}
				
				break;
			}
			default:
			{
				break;
			}
		}
	}

	for (auto it = itemLabels.begin(); it != itemLabels.end(); it++)
	{
		(*it)->setVisible(false);
		(*it)->setPositionX(0.0f);
		(*it)->setPositionY(0.0f);
		(*it)->setPositionZ(0.0f);
	}
	
	this->selectedItemIndex = filteredItemLabels.size() <= 0 ? 0 : MathUtils::clamp(this->selectedItemIndex, 0, filteredItemLabels.size() - 1);
	int adjustedIndex = this->selectedItemIndex - filteredItemLabels.size() / 2;
	float offset = float(adjustedIndex) * InventoryMenu::LabelSpacing;

	this->inventoryNodeContent->setPositionY(offset);
	this->itemPreview->clearPreview();

	if (filteredItemLabels.empty())
	{
		return;
	}

	const float offsetY = InventoryMenu::LabelSpacing * float(filteredItemLabels.size() / 2);
	index = 0;

	for (auto it = filteredItemLabels.begin(); it != filteredItemLabels.end(); it++, index++)
	{
		(*it)->setVisible(true);
		(*it)->setPositionY(float(index) * -InventoryMenu::LabelSpacing + offsetY);
	}

	if (this->activeFocus == ActiveFocus::Inventory)
	{
		const float XOffset = 16.0f;
		const float YOffset = 6.0f;
		const float ZOffset = 128.0f;

		filteredItemLabels[this->selectedItemIndex]->setPositionX(XOffset);
		filteredItemLabels[this->selectedItemIndex]->setPositionY(filteredItemLabels[this->selectedItemIndex]->getPositionY() + YOffset);
		filteredItemLabels[this->selectedItemIndex]->setPositionZ(ZOffset);

		this->itemPreview->preview(filteredItems[this->selectedItemIndex]);
	}
}

void InventoryMenu::toggleEquipSelectedItem()
{
	bool isSelectionInEquipment = this->selectedItemIndex < this->equippedItems.size();

	if (isSelectionInEquipment)
	{
		Item* selectedItem = this->equippedItems[this->selectedItemIndex];
		
		PlayerEquipment::getInstance()->tryTransact(PlayerInventory::getInstance(), selectedItem, nullptr, [=](Item* item, Item* otherItem)
		{
			// Success
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
		int adjustedIndex = this->selectedItemIndex - this->equippedItems.size();
		Item* selectedItem = this->inventoryItems[adjustedIndex];
		Item* equippedItem = nullptr;
		std::string selectedItemName = selectedItem == nullptr ? "" : selectedItem->getName();
		
		// Check if it's even an equipable item...
		if (dynamic_cast<Equipable*>(selectedItem) == nullptr)
		{
			return;
		}

		if (dynamic_cast<Hat*>(selectedItem))
		{
			equippedItem = PlayerEquipment::getInstance()->getHat();
		}
		else if (dynamic_cast<Weapon*>(selectedItem))
		{
			equippedItem = PlayerEquipment::getInstance()->getWeapon();
		}
		else if (dynamic_cast<Offhand*>(selectedItem))
		{
			equippedItem = PlayerEquipment::getInstance()->getOffhand();
		}
		
		PlayerInventory::getInstance()->tryTransact(PlayerEquipment::getInstance(), selectedItem, equippedItem, [=](Item* item, Item* otherItem)
		{
			// Success
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
}

cocos2d::Node* InventoryMenu::buildMenuLabel(LocalizedString* text, Sprite* icon)
{
	Node* contentNode = Node::create();

	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);

	label->setAnchorPoint(Vec2(0.0f, 0.5f));
	label->enableOutline(Color4B::BLACK, 2);
	label->setPositionX(-InventoryMenu::LabelSize.width / 2.0f);

	contentNode->addChild(label);

	if (icon != nullptr)
	{
		label->setPositionX(label->getPositionX() + 40.0f);
		contentNode->addChild(icon);

		icon->setPositionX(-InventoryMenu::LabelSize.width / 2.0f + 16.0f);
	}

	return contentNode;
}
