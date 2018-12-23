#include "PauseMenu.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/MenuBackground.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Exit.h"
#include "Strings/Menus/Options/Options.h"
#include "Strings/Menus/Pause.h"
#include "Strings/Menus/Resume.h"

using namespace cocos2d;

const Color3B PauseMenu::TitleColor = Color3B(88, 188, 193);

PauseMenu * PauseMenu::create()
{
	PauseMenu* instance = new PauseMenu();

	instance->autorelease();

	return instance;
}

PauseMenu::PauseMenu()
{
	this->pauseWindow = Sprite::create(UIResources::Menus_PauseMenu_PauseMenu);
	this->closeButton = MenuSprite::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->pauseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, LocaleStrings::Pause::create());
	this->resumeClickCallback = nullptr;
	this->optionsClickCallback = nullptr;
	this->exitClickCallback = nullptr;

	int fontSize = 24;
	Size shadowSize = Size(-2.0f, -2.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	LocalizedLabel*	resumeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, LocaleStrings::Resume::create());
	LocalizedLabel*	resumeLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, LocaleStrings::Resume::create());

	LocalizedLabel*	optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, LocaleStrings::Options::create());
	LocalizedLabel*	optionsLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, LocaleStrings::Options::create());

	LocalizedLabel*	exitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, LocaleStrings::Exit::create());
	LocalizedLabel*	exitLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, LocaleStrings::Exit::create());

	resumeLabel->setColor(textColor);
	resumeLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	resumeLabel->enableGlow(shadowColor);
	optionsLabel->setColor(textColor);
	optionsLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabel->enableGlow(shadowColor);
	exitLabel->setColor(textColor);
	exitLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabel->enableGlow(shadowColor);

	resumeLabelHover->setColor(highlightColor);
	resumeLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	resumeLabelHover->enableGlow(glowColor);
	optionsLabelHover->setColor(highlightColor);
	optionsLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabelHover->enableGlow(glowColor);
	exitLabelHover->setColor(highlightColor);
	exitLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabelHover->enableGlow(glowColor);

	this->resumeButton = TextMenuSprite::create(
		resumeLabel,
		resumeLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->optionsButton = TextMenuSprite::create(
		optionsLabel,
		optionsLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->exitButton = TextMenuSprite::create(
		exitLabel,
		exitLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->pauseLabel->setColor(PauseMenu::TitleColor);
	this->pauseLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	
	this->addChild(this->pauseWindow);
	this->addChild(this->pauseLabel);
	this->addChild(this->closeButton);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::onEnter()
{
	Hud::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->pauseWindow, delay, duration);
	GameUtils::fadeInObject(this->pauseLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->resumeButton, delay, duration);
	GameUtils::fadeInObject(this->optionsButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);
}

void PauseMenu::initializePositions()
{
	Hud::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->pauseWindow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->pauseLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 230.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2 + 136.0f, visibleSize.height / 2 + 204.0f));
	this->resumeButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 128.0f));
	this->optionsButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 0.0f));
	this->exitButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 180.0f));
}

void PauseMenu::initializeListeners()
{
	Hud::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(PauseMenu::onKeyPressed, this);

	this->resumeButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onResumeClick, this));
	this->optionsButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onOptionsClick, this));
	this->exitButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onExitClick, this));

	this->closeButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onCloseClick, this));
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->addEventListener(keyboardListener);
}

void PauseMenu::setResumeCallback(std::function<void()> resumeClickCallback)
{
	this->resumeClickCallback = resumeClickCallback;
}

void PauseMenu::setOptionsCallback(std::function<void()> optionsClickCallback)
{
	this->optionsClickCallback = optionsClickCallback;
}

void PauseMenu::setExitCallback(std::function<void()> exitClickCallback)
{
	this->exitClickCallback = exitClickCallback;
}

void PauseMenu::onExitConfirm()
{
	NavigationEvents::navigateTitle();
}

void PauseMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

			if (this->resumeClickCallback != nullptr)
			{
				this->resumeClickCallback();
			}

			break;
		}
	}
}

void PauseMenu::onCloseClick(MenuSprite* menuSprite)
{
	if (this->resumeClickCallback != nullptr)
	{
		this->resumeClickCallback();
	}
}

void PauseMenu::onResumeClick(MenuSprite* menuSprite)
{
	if (this->resumeClickCallback != nullptr)
	{
		this->resumeClickCallback();
	}
}

void PauseMenu::onOptionsClick(MenuSprite* menuSprite)
{
	if (this->optionsClickCallback != nullptr)
	{
		this->optionsClickCallback();
	}
}

void PauseMenu::onExitClick(MenuSprite* menuSprite)
{
	if (this->exitClickCallback != nullptr)
	{
		this->exitClickCallback();
	}
}
