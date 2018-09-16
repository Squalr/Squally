#include "PauseMenu.h"

const Color3B PauseMenu::TitleColor = Color3B(88, 188, 193);
const std::string PauseMenu::StringKeyMenuPause = "Menu_Pause";
const std::string PauseMenu::StringKeyResume = "Menu_Pause_Resume";
const std::string PauseMenu::StringKeyOptions = "Menu_Pause_Options";
const std::string PauseMenu::StringKeyExit = "Menu_Pause_Quit_To_Title";
const std::string PauseMenu::StringKeyExitPrompt = "Menu_Level_Prompt_Exit";

PauseMenu * PauseMenu::create()
{
	PauseMenu* pauseMenu = new PauseMenu();

	pauseMenu->autorelease();

	return pauseMenu;
}

PauseMenu::PauseMenu()
{
	this->background = Node::create();
	this->pauseWindow = Sprite::create(Resources::Menus_PauseMenu_PauseMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButton, Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);
	this->titleLabel = Label::create(Localization::resolveString(PauseMenu::StringKeyMenuPause), Localization::getMainFont(), 32.0f);

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
	Label* resumeLabelClicked = Label::create(Localization::resolveString(PauseMenu::StringKeyResume), Localization::getMainFont(), fontSize);

	Label* optionsLabel = Label::create(Localization::resolveString(PauseMenu::StringKeyOptions), Localization::getMainFont(), fontSize);
	Label* optionsLabelHover = Label::create(Localization::resolveString(PauseMenu::StringKeyOptions), Localization::getMainFont(), fontSize);
	Label* optionsLabelClicked = Label::create(Localization::resolveString(PauseMenu::StringKeyOptions), Localization::getMainFont(), fontSize);

	Label* exitLabel = Label::create(Localization::resolveString(PauseMenu::StringKeyExit), Localization::getMainFont(), fontSize);
	Label* exitLabelHover = Label::create(Localization::resolveString(PauseMenu::StringKeyExit), Localization::getMainFont(), fontSize);
	Label* exitLabelClicked = Label::create(Localization::resolveString(PauseMenu::StringKeyExit), Localization::getMainFont(), fontSize);

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

	resumeLabelClicked->setColor(highlightColor);
	resumeLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	resumeLabelClicked->enableGlow(glowColor);
	optionsLabelClicked->setColor(highlightColor);
	optionsLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabelClicked->enableGlow(glowColor);
	exitLabelClicked->setColor(highlightColor);
	exitLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabelClicked->enableGlow(glowColor);

	this->resumeButton = TextMenuSprite::create(
		resumeLabel,
		resumeLabelHover,
		resumeLabelClicked,
		Resources::Menus_Buttons_GenericButton,
		Resources::Menus_Buttons_GenericButtonHover,
		Resources::Menus_Buttons_GenericButtonClick);

	this->optionsButton = TextMenuSprite::create(
		optionsLabel,
		optionsLabelHover,
		optionsLabelClicked,
		Resources::Menus_Buttons_GenericButton,
		Resources::Menus_Buttons_GenericButtonHover,
		Resources::Menus_Buttons_GenericButtonClick);

	this->exitButton = TextMenuSprite::create(
		exitLabel,
		exitLabelHover,
		exitLabelClicked,
		Resources::Menus_Buttons_GenericButton,
		Resources::Menus_Buttons_GenericButtonHover,
		Resources::Menus_Buttons_GenericButtonClick);

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

	this->setFadeSpeed(0.0f);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->pauseWindow, delay, duration);
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->resumeButton, delay, duration);
	GameUtils::fadeInObject(this->optionsButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);

	this->background->addChild(MenuBackground::claimInstance());

	this->initializePositions();
	this->initializeListeners();
}

void PauseMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->pauseWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 230.0f));
	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 136.0f, origin.y + visibleSize.height / 2 + 204.0f));
	this->resumeButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 128.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 0.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 180.0f));

	MenuBackground::getInstance()->initializePositions();
}

void PauseMenu::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(PauseMenu::onKeyPressed, this);

	this->resumeButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onResumeClick, this));
	this->optionsButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onOptionsClick, this));
	this->exitButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onExitClick, this));

	this->closeButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onCloseClick, this));
	this->closeButton->setClickSound(Resources::Sounds_ClickBack1);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void PauseMenu::onExitConfirm()
{
	NavigationEvents::navigate(NavigationEvents::Title);
}

void PauseMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		event->stopPropagation();
		NavigationEvents::navigateBack();
		break;
	}
}

void PauseMenu::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}

void PauseMenu::onResumeClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}

void PauseMenu::onOptionsClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Options);
}

void PauseMenu::onExitClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateConfirm(Localization::resolveString(PauseMenu::StringKeyExitPrompt), CC_CALLBACK_0(PauseMenu::onExitConfirm, this), nullptr);
}
