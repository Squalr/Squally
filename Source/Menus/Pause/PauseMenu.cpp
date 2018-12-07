#include "PauseMenu.h"

const Color3B PauseMenu::TitleColor = Color3B(88, 188, 193);
const std::string PauseMenu::StringKeyMenuPause = "Menu_Pause";
const std::string PauseMenu::StringKeyResume = "Menu_Pause_Resume";
const std::string PauseMenu::StringKeyOptions = "Menu_Pause_Options";
const std::string PauseMenu::StringKeyExit = "Menu_Pause_Quit_To_Title";
const std::string PauseMenu::StringKeyExitPrompt = "Menu_Level_Prompt_Exit";

PauseMenu * PauseMenu::create()
{
	PauseMenu* instance = new PauseMenu();

	instance->autorelease();

	return instance;
}

PauseMenu::PauseMenu()
{
	this->background = Node::create();
	this->pauseWindow = Sprite::create(UIResources::Menus_PauseMenu_PauseMenu);
	this->closeButton = MenuSprite::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->titleLabel = Label::create(Localization::resolveString(PauseMenu::StringKeyMenuPause), Localization::getMainFont(), 32.0f);
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

	Label* resumeLabel = Label::create(Localization::resolveString(PauseMenu::StringKeyResume), Localization::getMainFont(), fontSize);
	Label* resumeLabelHover = Label::create(Localization::resolveString(PauseMenu::StringKeyResume), Localization::getMainFont(), fontSize);

	Label* optionsLabel = Label::create(Localization::resolveString(PauseMenu::StringKeyOptions), Localization::getMainFont(), fontSize);
	Label* optionsLabelHover = Label::create(Localization::resolveString(PauseMenu::StringKeyOptions), Localization::getMainFont(), fontSize);

	Label* exitLabel = Label::create(Localization::resolveString(PauseMenu::StringKeyExit), Localization::getMainFont(), fontSize);
	Label* exitLabelHover = Label::create(Localization::resolveString(PauseMenu::StringKeyExit), Localization::getMainFont(), fontSize);

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

	this->titleLabel->setColor(PauseMenu::TitleColor);
	this->titleLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	
	this->addChild(this->background);
	this->addChild(this->pauseWindow);
	this->addChild(this->titleLabel);
	this->addChild(this->closeButton);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);
	this->addChild(Mouse::create());
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
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
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
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 230.0f));
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
	NavigationEvents::navigate(NavigationEvents::Title);
}

void PauseMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
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
