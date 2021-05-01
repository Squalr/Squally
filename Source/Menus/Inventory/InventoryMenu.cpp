#include "InventoryMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Inventory/FilterMenu/FilterEntry.h"
#include "Menus/Inventory/FilterMenu/FilterMenu.h"
#include "Menus/Inventory/ItemMenu/ItemEntry.h"
#include "Menus/Inventory/ItemMenu/ItemMenu.h"
#include "Menus/Party/PartyMenu.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

InventoryMenu* InventoryMenu::create(LazyNode<PartyMenu>* partyMenu)
{
	InventoryMenu* instance = new InventoryMenu(partyMenu);

	instance->autorelease();

	return instance;
}

InventoryMenu::InventoryMenu(LazyNode<PartyMenu>* partyMenu)
{
	this->currencyInventory = nullptr;
	this->equipmentInventory = nullptr;
	this->inventory = nullptr;
	this->inventoryWindow = Sprite::create(UIResources::Menus_InventoryMenu_InventoryMenu);
	this->filterMenu = FilterMenu::create([=](){ this->onFilterChange(); });
	this->itemMenu = ItemMenu::create();
	this->inventoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Inventory_Inventory::create());
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->returnClickCallback = nullptr;
	this->equipmentChanged = false;
	this->partyMenu = partyMenu;

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
	
	this->addChild(this->inventoryWindow);
	this->addChild(this->filterMenu);
	this->addChild(this->itemMenu);
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

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForComponent<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
			this->equipmentInventory = entityInventoryBehavior->getEquipmentInventory();
			this->currencyInventory = entityInventoryBehavior->getCurrencyInventory();
		});
	}, Squally::MapKey);
}

void InventoryMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->filterMenu->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f, visibleSize.height / 2.0f - 44.0f));
	this->itemMenu->setPosition(Vec2(visibleSize.width / 2.0f - 1.0f, visibleSize.height / 2.0f - 44.0f));
	this->inventoryWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->inventoryLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void InventoryMenu::initializeListeners()
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
	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();
		this->close();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_D, InputEvents::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->filterMenu->unfocus();
		this->itemMenu->focus();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_A, InputEvents::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->filterMenu->focus();
		this->itemMenu->unfocus();
	});
}

void InventoryMenu::onFilterChange()
{
	this->itemMenu->clearPreview();
	this->populateItemList();
}

void InventoryMenu::populateItemList()
{
	this->itemMenu->clearVisibleItems();
	std::vector<Item*> equipment = this->filterMenu->getActiveFilter()->filter(this->equipmentInventory == nullptr ? std::vector<Item*>() : this->equipmentInventory->getItems());
	std::vector<Item*> items = this->filterMenu->getActiveFilter()->filter(this->inventory == nullptr ? std::vector<Item*>() : this->inventory->getItems());
	
	for (auto item : equipment)
	{
		ItemEntry* entry = this->itemMenu->pushVisibleItem(item, [=]()
		{
			this->performEquipmentAction(item);
		});

		entry->setEquipHintMode(ItemPreview::EquipHintMode::Unequip);
		entry->showIcon();
	}
	
	for (auto item : items)
	{
		ItemEntry* entry = this->itemMenu->pushVisibleItem(item, [=]()
		{
			this->performInventoryAction(item);
		});

		entry->setEquipHintMode(ItemPreview::EquipHintMode::Equip);
		entry->hideIcon();
	}

	this->itemMenu->updateAndPositionItemText();
}

void InventoryMenu::open()
{
	this->equipmentChanged = false;
	this->onFilterChange();
}

void InventoryMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void InventoryMenu::performEquipmentAction(Item* item)
{
	if (dynamic_cast<Equipable*>(item) != nullptr)
	{
		this->unequipItem(item);
	}
}

void InventoryMenu::performInventoryAction(Item* item)
{
	if (dynamic_cast<Equipable*>(item) != nullptr)
	{
		this->equipItem(item);
	}

	if (dynamic_cast<Consumable*>(item) != nullptr && dynamic_cast<Consumable*>(item)->canUseOutOfCombat())
	{
		this->consumeItem(dynamic_cast<Consumable*>(item));
	}
}

void InventoryMenu::equipItem(Item* item)
{
	if (this->inventory == nullptr || this->equipmentInventory == nullptr)
	{
		return;
	}

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

void InventoryMenu::unequipItem(Item* item)
{
	if (this->inventory == nullptr || this->equipmentInventory == nullptr)
	{
		return;
	}
	
	this->equipmentInventory->tryTransact(this->inventory, item, nullptr, [=](Item* item, Item* otherItem)
	{
		// Success unequipping item -- visually best if this ends up in the 1st inventory slot
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

void InventoryMenu::consumeItem(Consumable* item)
{
	if (item == nullptr)
	{
		return;
	}

	this->partyMenu->lazyGet()->setVisible(true);
	GameUtils::focus(this->partyMenu);

	int count = 0;
	
	for (Item* next : this->inventory->getItems())
	{
		if (next->getIdentifier() == item->getIdentifier())
		{
			count++;
		}
	}

	this->partyMenu->lazyGet()->openForSelection(item->getIconResource(), count, [=](PlatformerEntity* target)
	{
		return item->canUseOnTarget(target);
	},
	[=](PlatformerEntity* target)
	{
		int currentSelectionIndex = this->partyMenu->lazyGet()->getSelectionIndex();
		
		this->partyMenu->lazyGet()->setVisible(false);
		GameUtils::focus(this);

		item->useOutOfCombat(target);

		this->inventory->tryRemove(item, [=](Item* removedItem)
		{
			this->populateItemList();

			// Chain consumable usage
			for (auto next : this->inventory->getItems())
			{
				if (next->getIdentifier() == removedItem->getIdentifier())
				{
					this->consumeItem(dynamic_cast<Consumable*>(next));

					this->partyMenu->lazyGet()->setSelectionIndex(currentSelectionIndex);
					return;
				}
			}
		},
		[=](Item* removedItem)
		{
			// Failure
			LogUtils::logError("Error consuming item!");

			if (removedItem != nullptr)
			{
				LogUtils::logError(item->getName());
			}
		});
	},
	[=]()
	{
		this->partyMenu->lazyGet()->setVisible(false);
		GameUtils::focus(this);
	});
}

void InventoryMenu::close()
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
