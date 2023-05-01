#include "PlatformerPauseMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"

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

PlatformerPauseMenu* PlatformerPauseMenu::create()
{
	PlatformerPauseMenu* instance = new PlatformerPauseMenu();

	instance->autorelease();

	return instance;
}

PlatformerPauseMenu::PlatformerPauseMenu() : super(true)
{
	this->pauseWindow = Sprite::create(UIResources::Menus_PauseMenu_IngameMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_PauseMenu_CloseButton, UIResources::Menus_PauseMenu_CloseButtonSelected);
	this->pauseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Common_Empty::create());
	this->newButtonsNode = Node::create();
	
	this->inventoryButton = this->buildButton(
		UIResources::Menus_PauseMenu_InventoryButton,
		UIResources::Menus_PauseMenu_InventoryButtonSelected,
		Strings::Menus_Pause_Inventory::create(),
		true,
		Vec2(80.0f, -16.0f));
	this->optionsButton = this->buildButton(
		UIResources::Menus_PauseMenu_SettingsButton,
		UIResources::Menus_PauseMenu_SettingsButtonSelected,
		Strings::Menus_Pause_Options::create(),
		false,
		Vec2(-80.0f, 0.0f));
	this->quitToTitleButton = this->buildButton(
		UIResources::Menus_PauseMenu_ExitToTitleButton,
		UIResources::Menus_PauseMenu_ExitToTitleButtonSelected,
		Strings::Menus_Pause_QuitToTitle::create(),
		true,
		Vec2(80.0f, -8.0f));
	this->partyButton = this->buildButton(
		UIResources::Menus_PauseMenu_PartyButton,
		UIResources::Menus_PauseMenu_PartyButtonSelected,
		Strings::Menus_Pause_Party::create(),
		true,
		Vec2(80.0f, 0.0f));
	this->cardsButton = this->buildButton(
		UIResources::Menus_PauseMenu_CardsButton,
		UIResources::Menus_PauseMenu_CardsButtonSelected,
		Strings::Menus_Pause_Cards::create(),
		false,
		Vec2(-80.0f, 0.0f));
	this->collectablesButton = this->buildButton(
		UIResources::Menus_PauseMenu_CollectablesButton,
		UIResources::Menus_PauseMenu_CollectablesButtonSelected,
		Strings::Menus_Pause_Collectables::create(),
		true,
		Vec2(96.0f, 0.0f));
	this->lexiconButton = this->buildButton(
		UIResources::Menus_PauseMenu_LexiconButton,
		UIResources::Menus_PauseMenu_LexiconButtonSelected,
		Strings::Menus_Hacking_Lexicon_Lexicon::create(),
		false,
		Vec2(-80.0f, 0.0f));
	
	this->addChild(this->pauseWindow);
	this->addChild(this->pauseLabel);
	this->addChild(this->closeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->quitToTitleButton);
	this->addChild(this->inventoryButton);
	this->addChild(this->partyButton);
	this->addChild(this->cardsButton);
	this->addChild(this->collectablesButton);
	this->addChild(this->lexiconButton);
	this->addChild(this->newButtonsNode);
}

PlatformerPauseMenu::~PlatformerPauseMenu()
{
}

void PlatformerPauseMenu::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->pauseWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 368.0f));
	this->inventoryButton->setPosition(Vec2(visibleSize.width / 2.0f - 456.0f, visibleSize.height / 2.0f + 312.0f));
	this->optionsButton->setPosition(Vec2(visibleSize.width / 2.0f - 240.0f, visibleSize.height / 2.0f + 64.0f));
	this->quitToTitleButton->setPosition(Vec2(visibleSize.width / 2.0f - 538.0f, visibleSize.height / 2.0f - 144.0f));
	
	this->partyButton->setPosition(Vec2(visibleSize.width / 2.0f + 80.0f, visibleSize.height / 2.0f + 312.0f));
	this->cardsButton->setPosition(Vec2(visibleSize.width / 2.0f + 356.0f, visibleSize.height / 2.0f + 176.0f));
	this->collectablesButton->setPosition(Vec2(visibleSize.width / 2.0f + 64.0f, visibleSize.height / 2.0f + 16.0f));
	this->lexiconButton->setPosition(Vec2(visibleSize.width / 2.0f + 356.0f, visibleSize.height / 2.0f - 144.0f));
}

void PlatformerPauseMenu::initializeListeners()
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

	this->lexiconButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->lexiconClickCallback != nullptr)
		{
			this->lexiconClickCallback();
		}
	});
}

void PlatformerPauseMenu::disableInventory()
{
	this->inventoryButton->disableInteraction(128);
}

void PlatformerPauseMenu::disableCards()
{
	this->cardsButton->disableInteraction(128);
}

void PlatformerPauseMenu::disableCollectables()
{
	this->collectablesButton->disableInteraction(128);
}

void PlatformerPauseMenu::setInventoryClickCallback(std::function<void()> inventoryClickCallback)
{
	this->inventoryClickCallback = inventoryClickCallback;
}

void PlatformerPauseMenu::setPartyClickCallback(std::function<void()> partyClickCallback)
{
	this->partyClickCallback = partyClickCallback;
}

void PlatformerPauseMenu::setCardsClickCallback(std::function<void()> cardsClickCallback)
{
	this->cardsClickCallback = cardsClickCallback;
}

void PlatformerPauseMenu::setCollectablesClickCallback(std::function<void()> collectablesClickCallback)
{
	this->collectablesClickCallback = collectablesClickCallback;
}

void PlatformerPauseMenu::setLexiconClickCallback(std::function<void()> lexiconClickCallback)
{
	this->lexiconClickCallback = lexiconClickCallback;
}

ClickableTextNode* PlatformerPauseMenu::buildButton(std::string spriteResource, std::string spriteResourceSelected, LocalizedString* text, bool isLeftAligned,  Vec2 offset)
{
	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, text, CSize(256.0f, 112.0f), isLeftAligned ? TextHAlignment::LEFT : TextHAlignment::RIGHT);
	LocalizedLabel*	labelSelected = label->clone();

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

	label->enableOutline(Color4B::BLACK, 2);
	label->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	label->enableGlow(Color4B::BLACK);

	labelSelected->enableOutline(Color4B::BLACK, 2);
	labelSelected->setTextColor(Color4B::YELLOW);
	labelSelected->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	labelSelected->enableGlow(Color4B::BLACK);
	
	button->setTextOffset(offset);

	return button;
}
