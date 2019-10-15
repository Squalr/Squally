#include "InventoryMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Menus/Inventory/Filters/FilterMenu.h"
#include "Menus/Inventory/ItemMenu.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Inventory/Inventory.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

InventoryMenu* InventoryMenu::create()
{
	InventoryMenu* instance = new InventoryMenu();

	instance->autorelease();

	return instance;
}

InventoryMenu::InventoryMenu()
{
	this->currencyInventory = CurrencyInventory::create(SaveKeys::SaveKeySquallyCurrencyInventory);
	this->equipmentInventory = EquipmentInventory::create(SaveKeys::SaveKeySquallyEquipment);
	this->inventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);
	this->inventoryWindow = Sprite::create(UIResources::Menus_InventoryMenu_InventoryMenu);
	this->filterMenu = FilterMenu::create();
	this->itemMenu = ItemMenu::create();
	this->inventoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Inventory_Inventory::create());
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->returnClickCallback = nullptr;

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
	
	this->addChild(this->currencyInventory);
	this->addChild(this->equipmentInventory);
	this->addChild(this->inventory);
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

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->inventoryWindow, delay, duration);
	GameUtils::fadeInObject(this->inventoryLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
}

void InventoryMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->filterMenu->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f, visibleSize.height / 2.0f - 44.0f));
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
		
		args->handle();

		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
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

void InventoryMenu::open()
{
}

void InventoryMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}
