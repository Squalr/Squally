#include "IngameMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

IngameMenu* IngameMenu::create()
{
	IngameMenu* instance = new IngameMenu();

	instance->autorelease();

	return instance;
}

IngameMenu::IngameMenu() : super(true)
{
	this->pauseWindow = Sprite::create(UIResources::Menus_IngameMenu_IngameMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->pauseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Common_Empty::create());
	this->newButtonsNode = Node::create();
	this->addedButtons = std::vector<ClickableTextNode*>();
	this->resumeClickCallback = nullptr;
	this->optionsClickCallback = nullptr;
	this->quitToTitleClickCallback = nullptr;
	this->inventoryClickCallback = nullptr;
	this->partyClickCallback = nullptr;
	this->cardsClickCallback = nullptr;
	this->collectablesClickCallback = nullptr;

	this->resumeButton = nullptr;
	this->inventoryButton = this->buildButton(
		UIResources::Menus_IngameMenu_InventoryButton,
		UIResources::Menus_IngameMenu_InventoryButtonSelected,
		Strings::Menus_Pause_Inventory::create(),
		true,
		Vec2(80.0f, -16.0f));
	this->optionsButton = this->buildButton(
		UIResources::Menus_IngameMenu_SettingsButton,
		UIResources::Menus_IngameMenu_SettingsButtonSelected,
		Strings::Menus_Pause_Options::create(),
		false,
		Vec2(-80.0f, 0.0f));
	this->quitToTitleButton = this->buildButton(
		UIResources::Menus_IngameMenu_ExitToTitleButton,
		UIResources::Menus_IngameMenu_ExitToTitleButtonSelected,
		Strings::Menus_Pause_QuitToTitle::create(),
		true,
		Vec2(80.0f, -8.0f));
	this->partyButton = this->buildButton(
		UIResources::Menus_IngameMenu_PartyButton,
		UIResources::Menus_IngameMenu_PartyButtonSelected,
		Strings::Menus_Pause_Party::create(),
		true,
		Vec2(80.0f, 0.0f));
	this->cardsButton = this->buildButton(
		UIResources::Menus_IngameMenu_CardsButton,
		UIResources::Menus_IngameMenu_CardsButtonSelected,
		Strings::Menus_Pause_Cards::create(),
		false,
		Vec2(-80.0f, 0.0f));
	this->collectablesButton = this->buildButton(
		UIResources::Menus_IngameMenu_CollectablesButton,
		UIResources::Menus_IngameMenu_CollectablesButtonSelected,
		Strings::Menus_Pause_Collectables::create(),
		true,
		Vec2(96.0f, 0.0f));
	
	this->addChild(this->pauseWindow);
	this->addChild(this->pauseLabel);
	this->addChild(this->closeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->quitToTitleButton);
	this->addChild(this->inventoryButton);
	this->addChild(this->partyButton);
	this->addChild(this->cardsButton);
	this->addChild(this->collectablesButton);
	this->addChild(this->newButtonsNode);
}

IngameMenu::~IngameMenu()
{
}

void IngameMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	for (auto it = this->addedButtons.begin(); it != this->addedButtons.end(); it++)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}
}

void IngameMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->pauseWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 368.0f));
	this->inventoryButton->setPosition(Vec2(visibleSize.width / 2.0f - 456.0f, visibleSize.height / 2.0f + 296.0f));
	this->optionsButton->setPosition(Vec2(visibleSize.width / 2.0f - 240.0f, visibleSize.height / 2.0f + 64.0f));
	this->quitToTitleButton->setPosition(Vec2(visibleSize.width / 2.0f - 538.0f, visibleSize.height / 2.0f - 144.0f));
	this->partyButton->setPosition(Vec2(visibleSize.width / 2.0f + 80.0f, visibleSize.height / 2.0f + 296.0f));
	this->cardsButton->setPosition(Vec2(visibleSize.width / 2.0f + 356.0f, visibleSize.height / 2.0f + 96.0f));
	this->collectablesButton->setPosition(Vec2(visibleSize.width / 2.0f + 104.0f, visibleSize.height / 2.0f - 128.0f));
}

void IngameMenu::initializeListeners()
{
	super::initializeListeners();

	this->inventoryButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->inventoryClickCallback != nullptr)
		{
			this->inventoryClickCallback();
		}
	});
	
	this->partyButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->partyClickCallback != nullptr)
		{
			this->partyClickCallback();
		}
	});
	
	this->cardsButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->cardsClickCallback != nullptr)
		{
			this->cardsClickCallback();
		}
	});
	
	this->collectablesButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->collectablesClickCallback != nullptr)
		{
			this->collectablesClickCallback();
		}
	});
}

void IngameMenu::setInventoryClickCallback(std::function<void()> inventoryClickCallback)
{
	this->inventoryClickCallback = inventoryClickCallback;
}

void IngameMenu::setPartyClickCallback(std::function<void()> partyClickCallback)
{
	this->partyClickCallback = partyClickCallback;
}

void IngameMenu::setCardsClickCallback(std::function<void()> cardsClickCallback)
{
	this->cardsClickCallback = cardsClickCallback;
}

void IngameMenu::setCollectablesClickCallback(std::function<void()> collectablesClickCallback)
{
	this->collectablesClickCallback = collectablesClickCallback;
}

ClickableTextNode* IngameMenu::buildButton(std::string spriteResource, std::string spriteResourceSelected, LocalizedString* text, bool isLeftAligned,  Vec2 offset)
{
	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, text);
	LocalizedLabel*	labelSelected = label->clone();

	label->enableOutline(Color4B::BLACK, 2);
	label->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	label->enableGlow(Color4B::BLACK);

	labelSelected->enableOutline(Color4B::BLACK, 2);
	labelSelected->setTextColor(Color4B::YELLOW);
	labelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	labelSelected->enableGlow(Color4B::BLACK);

	ClickableTextNode* button = ClickableTextNode::create(
		label,
		labelSelected,
		spriteResource,
		spriteResourceSelected);

	if (isLeftAligned)
	{
		label->setAnchorPoint(Vec2(0.0f, 0.5f));
		labelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
	else
	{
		label->setAnchorPoint(Vec2(1.0f, 0.5f));
		labelSelected->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	
	button->setTextOffset(offset);

	return button;
}
