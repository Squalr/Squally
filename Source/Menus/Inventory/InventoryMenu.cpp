#include "InventoryMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Inventory/All.h"
#include "Strings/Menus/Inventory/Consumables.h"
#include "Strings/Menus/Inventory/Crafting.h"
#include "Strings/Menus/Inventory/Equipment.h"
#include "Strings/Menus/Inventory/Inventory.h"
#include "Strings/Menus/Inventory/Misc.h"
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
	this->inventoryWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->equipmentPanel = Sprite::create(UIResources::Menus_InventoryMenu_EquipmentMenu);
	this->filterNode = Node::create();
	this->closeButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->inventoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Inventory_Inventory::create());
	this->returnClickCallback = nullptr;
	this->activeFocus = ActiveFocus::Filter;

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

	this->allLabel = this->buildMenuLabel(Strings::Menus_Inventory_All::create());
	this->equipmentLabel = this->buildMenuLabel(Strings::Menus_Inventory_Equipment::create());
	this->consumablesLabel = this->buildMenuLabel(Strings::Menus_Inventory_Consumables::create());
	this->craftingLabel = this->buildMenuLabel(Strings::Menus_Inventory_Crafting::create());
	this->miscLabel = this->buildMenuLabel(Strings::Menus_Inventory_Misc::create());
	
	this->filterNode->addChild(this->allLabel);
	this->filterNode->addChild(this->equipmentLabel);
	this->filterNode->addChild(this->consumablesLabel);
	this->filterNode->addChild(this->craftingLabel);
	this->filterNode->addChild(this->miscLabel);
	this->addChild(this->inventoryWindow);
	this->addChild(this->equipmentPanel);
	this->addChild(this->filterNode);
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

	this->inventoryWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->filterNode->setPosition(Vec2(visibleSize.width / 2.0f - 480.0f, visibleSize.height / 2.0f - 32.0f));
	this->equipmentPanel->setPosition(Vec2(visibleSize.width / 2.0f + 292.0f, visibleSize.height / 2.0f + 64.0f));
	this->inventoryLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));

	const int count = 5;
	const float spacing = 96.0f;
	const float offsetY = spacing * float(count / 2);

	this->allLabel->setPositionY(0.0f * -spacing + offsetY);
	this->equipmentLabel->setPositionY(1.0f * -spacing + offsetY);
	this->consumablesLabel->setPositionY(2.0f * -spacing + offsetY);
	this->craftingLabel->setPositionY(3.0f * -spacing + offsetY);
	this->miscLabel->setPositionY(4.0f * -spacing + offsetY);
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

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->activeFocus = ActiveFocus::Inventory;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->activeFocus = ActiveFocus::Filter;
	});
}

void InventoryMenu::setReturnCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

ClickableTextNode* InventoryMenu::buildMenuLabel(LocalizedString* text)
{
	static const Size LabelSize = Size(128.0f, 32.0f);

	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);
	LocalizedLabel*	labelSelected = label->clone();
	Node* frameNode = Node::create();
	Node* frameNodeSelected = Node::create();

	label->setAnchorPoint(Vec2(0.0f, 0.5f));
	labelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
	frameNode->setAnchorPoint(Vec2(0.0f, 0.5f));
	frameNodeSelected->setAnchorPoint(Vec2(0.0f, 0.5f));

	frameNode->setContentSize(LabelSize);
	frameNodeSelected->setContentSize(LabelSize);

	label->enableOutline(Color4B::BLACK, 2);
	label->enableGlow(Color4B::BLACK);
	labelSelected->enableOutline(Color4B::BLACK, 2);
	labelSelected->setTextColor(Color4B::YELLOW);
	labelSelected->enableGlow(Color4B::ORANGE);

	ClickableTextNode* menuLabel = ClickableTextNode::create(label, labelSelected, frameNode, frameNodeSelected);

	menuLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	menuLabel->setContentSize(Size(128.0f, 32.0f));

	return menuLabel;
}
