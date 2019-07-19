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
	this->filterNode = Node::create();
	this->filterNodeContent = Node::create();
	this->inventoryNode = Node::create();
	this->inventoryNodeContent = Node::create();
	this->filterSelectionArrow = Sprite::create(UIResources::Menus_InventoryMenu_Arrow);
	this->filterSelectedArrow =  Sprite::create(UIResources::Menus_InventoryMenu_Pointer);
	this->inventorySelectionArrow = Sprite::create(UIResources::Menus_InventoryMenu_Arrow);
	this->closeButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->inventoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Inventory_Inventory::create());
	this->returnClickCallback = nullptr;
	this->activeFocus = ActiveFocus::Filter;
	this->activeFilter = ActiveFilter::All;
	this->filterLabels = std::vector<ClickableTextNode*>();

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
	this->filterNode->addChild(this->filterNodeContent);
	this->inventoryNode->addChild(this->inventoryNodeContent);
	this->addChild(this->inventoryWindow);
	this->addChild(this->equipmentPanel);
	this->addChild(this->filterNode);
	this->addChild(this->inventoryNode);
	this->addChild(this->filterSelectionArrow);
	this->addChild(this->filterSelectedArrow);
	this->addChild(this->inventorySelectionArrow);
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

	this->unfocusInventory();
	this->setActiveFilter(ActiveFilter::All);
}

void InventoryMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->inventoryWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->filterNode->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f, visibleSize.height / 2.0f - 32.0f));
	this->inventoryNode->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f + 342.0f, visibleSize.height / 2.0f - 32.0f));
	this->filterSelectionArrow->setPosition(Vec2(visibleSize.width / 2.0f - 524.0f, visibleSize.height / 2.0f - 44.0f));
	this->filterSelectedArrow->setPosition(Vec2(visibleSize.width / 2.0f - 524.0f, visibleSize.height / 2.0f - 44.0f));
	this->inventorySelectionArrow->setPosition(Vec2(visibleSize.width / 2.0f - 192.0f, visibleSize.height / 2.0f - 44.0f));
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

	this->allLabel->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->setActiveFilter(ActiveFilter::All);
		this->focusInventory();
	});

	this->equipmentLabel->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->setActiveFilter(ActiveFilter::Equipment);
		this->focusInventory();
	});

	this->consumablesLabel->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->setActiveFilter(ActiveFilter::Consumables);
		this->focusInventory();
	});

	this->craftingLabel->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->setActiveFilter(ActiveFilter::Crafting);
		this->focusInventory();
	});

	this->miscLabel->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->setActiveFilter(ActiveFilter::Misc);
		this->focusInventory();
	});
}

void InventoryMenu::setReturnCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void InventoryMenu::setActiveFilter(ActiveFilter activeFilter)
{
	this->activeFilter = activeFilter;

	this->positionScrolls();
}

void InventoryMenu::scrollFilterUp()
{
	switch(this->activeFilter)
	{
		case ActiveFilter::All:
		{
			this->setActiveFilter(ActiveFilter::Misc);
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

	this->positionScrolls();
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
			this->setActiveFilter(ActiveFilter::All);
			break;
		}
		default:
		{
			break;
		}
	}

	this->positionScrolls();
}

void InventoryMenu::scrollInventoryUp()
{
	this->positionScrolls();
}

void InventoryMenu::scrollInventoryDown()
{
	this->positionScrolls();
}

void InventoryMenu::unfocusInventory()
{
	this->activeFocus = ActiveFocus::Filter;
	this->filterSelectionArrow->setVisible(true);
	this->filterSelectedArrow->setVisible(false);
	this->inventorySelectionArrow->setVisible(false);
}

void InventoryMenu::focusInventory()
{
	this->activeFocus = ActiveFocus::Inventory;
	this->filterSelectionArrow->setVisible(false);
	this->filterSelectedArrow->setVisible(true);
	this->inventorySelectionArrow->setVisible(true);

	switch (this->activeFilter)
	{
		case ActiveFilter::All:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}

void InventoryMenu::positionScrolls()
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
	const float YOffset = 8.0f;
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

ClickableTextNode* InventoryMenu::buildMenuLabel(LocalizedString* text)
{
	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);
	LocalizedLabel*	labelSelected = label->clone();
	Node* frameNode = Node::create();
	Node* frameNodeSelected = Node::create();

	label->setAnchorPoint(Vec2(0.0f, 0.5f));
	labelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
	frameNode->setAnchorPoint(Vec2(0.0f, 0.5f));
	frameNodeSelected->setAnchorPoint(Vec2(0.0f, 0.5f));

	frameNode->setContentSize(InventoryMenu::LabelSize);
	frameNodeSelected->setContentSize(InventoryMenu::LabelSize);

	label->enableOutline(Color4B::BLACK, 2);
	labelSelected->enableOutline(Color4B::BLACK, 2);
	labelSelected->setTextColor(Color4B::YELLOW);

	ClickableTextNode* menuLabel = ClickableTextNode::create(label, labelSelected, frameNode, frameNodeSelected);

	label->setPositionX(-InventoryMenu::LabelSize.width / 2.0f);
	labelSelected->setPositionX(-InventoryMenu::LabelSize.width / 2.0f);

	menuLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	menuLabel->setContentSize(Size(InventoryMenu::LabelSize.width, InventoryMenu::LabelSize.height));

	return menuLabel;
}
