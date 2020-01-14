#include "CraftingMenu.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Inventory/FilterMenu/FilterEntry.h"
#include "Menus/Inventory/FilterMenu/FilterMenu.h"
#include "Menus/Inventory/ItemMenu/ItemEntry.h"
#include "Menus/Inventory/ItemMenu/ItemMenu.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const int CraftingMenu::MinHexusCards = 20;
const int CraftingMenu::MaxHexusCards = 60;

CraftingMenu* CraftingMenu::create()
{
	CraftingMenu* instance = new CraftingMenu();

	instance->autorelease();

	return instance;
}

CraftingMenu::CraftingMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);
	this->currencyInventory = CurrencyInventory::create(SaveKeys::SaveKeySquallyCurrencyInventory);
	this->equipmentInventory = EquipmentInventory::create(SaveKeys::SaveKeySquallyEquipment);
	this->inventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);
	this->craftingWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->filterMenu = FilterMenu::create([=](){ this->onFilterChange(); });
	this->itemMenu = ItemMenu::create();
	this->craftingLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Crafting_Crafting::create());
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->returnClickCallback = nullptr;
	this->equipmentChanged = false;

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

	this->craftingLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->craftingLabel->enableGlow(Color4B::BLACK);
	
	this->addChild(this->backdrop);
	this->addChild(this->currencyInventory);
	this->addChild(this->equipmentInventory);
	this->addChild(this->inventory);
	this->addChild(this->craftingWindow);
	this->addChild(this->filterMenu);
	this->addChild(this->itemMenu);
	this->addChild(this->craftingLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

CraftingMenu::~CraftingMenu()
{
}

void CraftingMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->craftingWindow, delay, duration);
	GameUtils::fadeInObject(this->craftingLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
}

void CraftingMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->filterMenu->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f, visibleSize.height / 2.0f - 44.0f));
	this->itemMenu->setPosition(Vec2(visibleSize.width / 2.0f - 1.0f, visibleSize.height / 2.0f - 44.0f));
	this->craftingWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->craftingLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CraftingMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();
		this->close();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->filterMenu->unfocus();
		this->itemMenu->focus();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->filterMenu->focus();
		this->itemMenu->unfocus();
	});
}

void CraftingMenu::onFilterChange()
{
	this->populateItemList();
	this->itemMenu->clearPreview();
}

void CraftingMenu::populateItemList()
{
	this->itemMenu->clearVisibleItems();
	std::vector<Item*> equipment = this->filterMenu->getActiveFilter()->filter(this->equipmentInventory->getItems());
	std::vector<Item*> items = this->filterMenu->getActiveFilter()->filter(this->inventory->getItems());
	
	for (auto it = equipment.begin(); it != equipment.end(); it++)
	{
		Item* item = *it;

		ItemEntry* entry = this->itemMenu->pushVisibleItem(item, [=]()
		{
			this->performEquipmentAction(item);
		});

		entry->showIcon();
	}
	
	for (auto it = items.begin(); it != items.end(); it++)
	{
		Item* item = *it;

		ItemEntry* entry = this->itemMenu->pushVisibleItem(item, [=]()
		{
			this->performInventoryAction(item);
		});

		entry->hideIcon();
	}

	this->itemMenu->updateAndPositionItemText();
}

void CraftingMenu::open()
{
	this->equipmentChanged = false;
	this->onFilterChange();
}

void CraftingMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void CraftingMenu::performEquipmentAction(Item* item)
{
	if (dynamic_cast<HexusCard*>(item) != nullptr)
	{
		this->unequipHexusCard(item);
	}
	else if (dynamic_cast<Equipable*>(item) != nullptr)
	{
		this->unequipItem(item);
	}
}

void CraftingMenu::performInventoryAction(Item* item)
{
	if (dynamic_cast<HexusCard*>(item) != nullptr)
	{
		this->equipHexusCard(item);
	}
	else if (dynamic_cast<Equipable*>(item) != nullptr)
	{
		this->equipItem(item);
	}
}

void CraftingMenu::equipHexusCard(Item* card)
{
	if (this->equipmentInventory->getHexusCards().size() >= CraftingMenu::MaxHexusCards)
	{
		return;
	}

	this->inventory->tryTransact(this->equipmentInventory, card, nullptr, [=](Item* item, Item* otherItem)
	{
		this->equipmentInventory->moveItem(item, this->equipmentInventory->getItems().size());

		this->populateItemList();
	},
	[=](Item* item, Item* otherItem)
	{
		// Failure
		LogUtils::logError("Error equipping card!");

		if (item != nullptr)
		{
			LogUtils::logError(item->getName());
		}

		if (otherItem != nullptr)
		{
			LogUtils::logError(otherItem->getName());
		}
	});
}

void CraftingMenu::unequipHexusCard(Item* card)
{
	if (this->equipmentInventory->getHexusCards().size() <= CraftingMenu::MinHexusCards)
	{
		return;
	}

	this->equipmentInventory->tryTransact(this->inventory, card, nullptr, [=](Item* item, Item* otherItem)
	{
		// Success unequipping item -- visually best if this ends up in the 1st crafting slot
		this->inventory->moveItem(item, 0);

		this->populateItemList();
	},
	[=](Item* item, Item* otherItem)
	{
		// Failure
		LogUtils::logError("Error unequipping card!");

		if (otherItem != nullptr)
		{
			LogUtils::logError(otherItem->getName());
		}
	});
}

void CraftingMenu::equipItem(Item* item)
{
	Item* equippedItem = nullptr;

	if (dynamic_cast<Hat*>(item))
	{
		equippedItem = this->equipmentInventory->getHat();
	}
	else if (dynamic_cast<Weapon*>(item))
	{
		equippedItem = this->equipmentInventory->getWeapon();
	}
	else if (dynamic_cast<Offhand*>(item))
	{
		equippedItem = this->equipmentInventory->getOffhand();
	}
	
	this->inventory->tryTransact(this->equipmentInventory, item, equippedItem, [=](Item* item, Item* otherItem)
	{
		// Success equipping item. Adjust final position if equipping an item without a swap
		if (otherItem == nullptr)
		{
			this->equipmentInventory->moveItem(item, this->equipmentInventory->getItems().size());
		}

		this->populateItemList();
		this->equipmentChanged = true;
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
}

void CraftingMenu::unequipItem(Item* item)
{
	this->equipmentInventory->tryTransact(this->inventory, item, nullptr, [=](Item* item, Item* otherItem)
	{
		// Success unequipping item -- visually best if this ends up in the 1st crafting slot
		this->inventory->moveItem(item, 0);
		
		this->populateItemList();
		this->equipmentChanged = true;
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
}

void CraftingMenu::close()
{
	if (this->equipmentChanged)
	{
		PlatformerEvents::TriggerEquippedItemsChanged();
	}
	
	if (this->returnClickCallback != nullptr)
	{
		this->returnClickCallback();
	}
}
