#include "CardsMenu.h"

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
#include "Menus/Inventory/FilterMenu/HexusFilter.h"
#include "Menus/Inventory/ItemMenu/ItemEntry.h"
#include "Menus/Inventory/ItemMenu/ItemMenu.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardPreview.h"
#include "Scenes/Hexus/HelpMenus/HelpMenu.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
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

const int CardsMenu::MinHexusCards = 20;
const int CardsMenu::MaxHexusCards = 60;

CardsMenu* CardsMenu::create()
{
	CardsMenu* instance = new CardsMenu();

	instance->autorelease();

	return instance;
}

CardsMenu::CardsMenu()
{
	this->cardsWindow = Sprite::create(UIResources::Menus_InventoryMenu_InventoryMenu);
	this->equippedCardsMenu = ItemMenu::create();
	this->unequippedCardsMenu = ItemMenu::create();
	this->cardsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Cards_Cards::create());
	this->hexusFilter = HexusFilter::create();
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->helpMenu = LazyNode<HelpMenu>::create(CC_CALLBACK_0(CardsMenu::buildHelpMenu, this));
	this->inventory = nullptr;
	this->equipmentInventory = nullptr;
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

	this->cardsLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->cardsLabel->enableGlow(Color4B::BLACK);
	this->hexusFilter->setVisible(false);

	this->unequippedCardsMenu->setTextOffset(ItemMenu::DefaultTextOffset + Vec3(50.0f, 0.0f, 0.0f));
	
	this->addChild(this->cardsWindow);
	this->addChild(this->equippedCardsMenu);
	this->addChild(this->unequippedCardsMenu);
	this->addChild(this->hexusFilter);
	this->addChild(this->cardsLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
	this->addChild(this->helpMenu);
}

CardsMenu::~CardsMenu()
{
}

void CardsMenu::onEnter()
{
	super::onEnter();
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
			this->equipmentInventory = entityInventoryBehavior->getEquipmentInventory();
		});
	}, Squally::MapKey);
}

void CardsMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->unequippedCardsMenu->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f, visibleSize.height / 2.0f - 44.0f));
	this->equippedCardsMenu->setPosition(Vec2(visibleSize.width / 2.0f - 1.0f, visibleSize.height / 2.0f - 44.0f));
	this->unequippedCardsMenu->setPreviewOffset(ItemMenu::DefaultPreviewOffset + (this->equippedCardsMenu->getPosition() - this->unequippedCardsMenu->getPosition()));
	this->cardsWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->cardsLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CardsMenu::initializeListeners()
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

	this->equippedCardsMenu->getItemPreview()->getCardPreview()->setHelpClickCallback([=](CardData* cardData)
	{
		this->showHelpMenu(cardData);
	});

	this->unequippedCardsMenu->getItemPreview()->getCardPreview()->setHelpClickCallback([=](CardData* cardData)
	{
		this->showHelpMenu(cardData);
	});

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
		this->equippedCardsMenu->focus();
		this->unequippedCardsMenu->unfocus();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_A, InputEvents::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->equippedCardsMenu->unfocus();
		this->unequippedCardsMenu->focus();
	});
}

void CardsMenu::populateItemList()
{
	this->equippedCardsMenu->clearVisibleItems();
	this->unequippedCardsMenu->clearVisibleItems();
	std::vector<Item*> equipment = this->hexusFilter->filter(this->equipmentInventory == nullptr ? std::vector<Item*>() : this->equipmentInventory->getItems());
	std::vector<Item*> items = this->hexusFilter->filter(this->inventory == nullptr ? std::vector<Item*>() : this->inventory->getItems());

	auto sortLambda = [](Item* a, Item* b)
	{
		HexusCard* cardA = dynamic_cast<HexusCard*>(a);
		HexusCard* cardB = dynamic_cast<HexusCard*>(b);

		if (cardA == nullptr)
		{
			return false;
		}
		else if (cardB == nullptr)
		{
			return false;
		}

		CardData* dataA = CardList::getInstance()->cardListByName[cardA->getCardKey()];
		CardData* dataB = CardList::getInstance()->cardListByName[cardB->getCardKey()];

		// Non-matching types, just sort these by card type
		if (dataA->getCardType() != dataB->getCardType())
		{
			return dataA->getCardType() < dataB->getCardType();
		}

		switch (dataA->getCardType())
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
			{
				// Sort by attack
				return dataA->getAttack() < dataB->getAttack();
				break;
			}
			default:
			{
				// Sort by card type
				return dataA->getCardType() < dataB->getCardType();
			}
		}
	};
	
	std::sort(equipment.begin(), equipment.end(), sortLambda);
	std::sort(items.begin(), items.end(), sortLambda);
	
	for (auto item : equipment)
	{
		ItemEntry* entry = this->equippedCardsMenu->pushVisibleItem(item, [=]()
		{
			if (dynamic_cast<HexusCard*>(item) != nullptr)
			{
				this->unequipHexusCard(dynamic_cast<HexusCard*>(item));
			}
		});

		entry->setEquipHintMode(ItemPreview::EquipHintMode::Unequip);
		entry->showIcon();
	}
	
	for (auto item : items)
	{
		ItemEntry* entry = this->unequippedCardsMenu->pushVisibleItem(item, [=]()
		{
			if (dynamic_cast<HexusCard*>(item) != nullptr)
			{
				this->equipHexusCard(dynamic_cast<HexusCard*>(item));
			}
		});

		entry->setEquipHintMode(ItemPreview::EquipHintMode::Equip);
		entry->hideIcon();
	}

	this->equippedCardsMenu->updateAndPositionItemText();
	this->unequippedCardsMenu->updateAndPositionItemText();
}

void CardsMenu::open()
{
	this->equipmentChanged = false;
	this->populateItemList();
	this->equippedCardsMenu->clearPreview();
	this->unequippedCardsMenu->clearPreview();
	
	this->equippedCardsMenu->focus();
	this->unequippedCardsMenu->unfocus();
}

void CardsMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void CardsMenu::equipHexusCard(HexusCard* card)
{
	if (this->equipmentInventory == nullptr || this->inventory == nullptr)
	{
		return;
	}

	if (this->equipmentInventory->getHexusCards().size() >= CardsMenu::MaxHexusCards)
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

void CardsMenu::unequipHexusCard(HexusCard* card)
{
	if (this->equipmentInventory == nullptr || this->inventory == nullptr)
	{
		return;
	}
	
	if (this->equipmentInventory->getHexusCards().size() <= CardsMenu::MinHexusCards)
	{
		return;
	}

	this->equipmentInventory->tryTransact(this->inventory, card, nullptr, [=](Item* item, Item* otherItem)
	{
		// Success unequipping item -- visually best if this ends up in the 1st inventory slot
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

void CardsMenu::showHelpMenu(CardData* cardData)
{
	this->helpMenu->lazyGet()->openMenu(cardData);

	this->cardsWindow->setVisible(false);
	this->returnButton->setVisible(false);
	this->closeButton->setVisible(false);

	GameUtils::focus(this->helpMenu);
}

void CardsMenu::close()
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

HelpMenu* CardsMenu::buildHelpMenu()
{
	HelpMenu* instance = HelpMenu::create();

	instance->setExitCallback([=]()
	{
		instance->setVisible(false);
		this->cardsWindow->setVisible(true);
		this->returnButton->setVisible(true);
		this->closeButton->setVisible(true);

		GameUtils::focus(this);
	});

	return instance;
}
