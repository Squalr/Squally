#include "CipherMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Options/GeneralTab.h"
#include "Menus/Options/LanguageTab.h"
#include "Menus/Options/MemesTab.h"
#include "Menus/Options/VideoTab.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Cancel.h"
#include "Strings/Menus/Options/Options.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

const Color3B CipherMenu::TitleColor = Color3B(88, 188, 193);

CipherMenu* CipherMenu::create()
{
	CipherMenu* instance = new CipherMenu();

	instance->autorelease();

	return instance;
}

CipherMenu::CipherMenu()
{
	this->backClickCallback = nullptr;

	this->background = Node::create();
	this->optionsWindow = Sprite::create(UIResources::Menus_CipherMenu_CipherMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton2, UIResources::Menus_Buttons_CloseButton2Select);
	this->leftPanel = Node::create();
	this->rightPanel = Node::create();
	this->optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Options_Options::create());

	this->optionsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	LocalizedLabel*	cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Cancel::create());
	LocalizedLabel*	cancelLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Cancel::create());

	cancelLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabel->enableGlow(Color4B::BLACK);

	cancelLabelHover->setColor(Color3B::YELLOW);
	cancelLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabelHover->enableGlow(Color4B::ORANGE);

	this->cancelButton = ClickableTextNode::create(
		cancelLabel,
		cancelLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());

	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);

	returnLabelHover->setColor(Color3B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->addChild(this->background);
	this->addChild(this->optionsWindow);
	this->addChild(this->leftPanel);
	this->addChild(this->rightPanel);
	this->addChild(this->optionsLabel);
	this->addChild(this->closeButton);
	this->addChild(this->cancelButton);
	this->addChild(this->returnButton);
}

CipherMenu::~CipherMenu()
{
}

void CipherMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->optionsWindow, delay, duration);
	GameUtils::fadeInObject(this->optionsLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->cancelButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
	GameUtils::fadeInObject(this->leftPanel, delay, duration);
	GameUtils::fadeInObject(this->rightPanel, delay, duration);
}

void CipherMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(CipherEvents::EventOpenCipher, [=](EventCustom* eventCustom)
	{
		this->setVisible(true);
	}));

	this->cancelButton->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onMenuCancel();  });
	this->returnButton->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onMenuExit();  });
	this->closeButton->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onMenuExit();  });

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(CipherMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void CipherMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->optionsWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->optionsLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 372.0f));
	this->leftPanel->setPosition(Vec2(visibleSize.width / 2.0f - 376.0f, visibleSize.height / 2.0f + 278.0f));
	this->rightPanel->setPosition(Vec2(visibleSize.width / 2.0f + 160.0f, visibleSize.height / 2.0f + 52.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 510.0f, visibleSize.height / 2.0f + 364.0f));

	const float offsetY = 48.0f;

	this->cancelButton->setPosition(Vec2(visibleSize.width / 2.0f - 80.0f, visibleSize.height / 2.0f - 348.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f + 356.0f, visibleSize.height / 2.0f - 348.0f));
}

void CipherMenu::setBackClickCallback(std::function<void()> backClickCallback)
{
	this->backClickCallback = backClickCallback;
}

void CipherMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			this->onMenuExit();
			break;
		}
		default:
		{
			break;
		}
	}
}

void CipherMenu::onMenuCancel()
{
	if (this->backClickCallback != nullptr)
	{
		this->backClickCallback();
	}
}

void CipherMenu::onMenuExit()
{
	ConfigManager::save();

	if (this->backClickCallback != nullptr)
	{
		this->backClickCallback();
	}
}
