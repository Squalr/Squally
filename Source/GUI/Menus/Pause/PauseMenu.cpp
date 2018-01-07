#include "PauseMenu.h"

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
	this->closeButton = MenuSprite::create(Sprite::create(Resources::Menus_Buttons_CloseButton), Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);
	this->resumeButton = MenuSprite::create(Sprite::create(Resources::Menus_PauseMenu_ResumeButton), Resources::Menus_PauseMenu_ResumeButtonHover, Resources::Menus_PauseMenu_ResumeButtonClick);
	this->optionsButton = MenuSprite::create(Sprite::create(Resources::Menus_PauseMenu_OptionsButton), Resources::Menus_PauseMenu_OptionsButtonHover, Resources::Menus_PauseMenu_OptionsButtonClick);
	this->exitButton = MenuSprite::create(Sprite::create(Resources::Menus_PauseMenu_QuitButton), Resources::Menus_PauseMenu_QuitButtonHover, Resources::Menus_PauseMenu_QuitButtonClick);

	this->resumeButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onResumeClick, this));
	this->optionsButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onOptionsClick, this));
	this->exitButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onExitClick, this));

	this->closeButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onCloseClick, this));
	this->closeButton->setClickSound(Resources::Sounds_ClickBack1);

	this->addChild(this->background);
	this->addChild(this->pauseWindow);
	this->addChild(this->closeButton);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);

	this->initializeListeners();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	Utils::fadeInObject(this->pauseWindow, delay, duration);
	Utils::fadeInObject(this->closeButton, delay, duration);
	Utils::fadeInObject(this->resumeButton, delay, duration);
	Utils::fadeInObject(this->optionsButton, delay, duration);
	Utils::fadeInObject(this->exitButton, delay, duration);

	this->background->addChild(MenuBackground::claimInstance());

	this->initializePositions();

	this->addChild(Mouse::claimInstance());
}

void PauseMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->pauseWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 136.0f, origin.y + visibleSize.height / 2 + 204.0f));
	this->resumeButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 128.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 0.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 180.0f));

	MenuBackground::getInstance()->initializePositions();
}

void PauseMenu::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PauseMenu::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void PauseMenu::onExitConfirm()
{
	Director::getInstance()->popToSceneStackLevel(2);
}

// Implementation of the keyboard event callback function prototype
void PauseMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->popScene();
		break;
	}
}

void PauseMenu::onCloseClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();
}

void PauseMenu::onResumeClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();
}

void PauseMenu::onOptionsClick(MenuSprite* menuSprite)
{
	Director::getInstance()->pushScene(OptionsMenu::create());
}

void PauseMenu::onExitClick(MenuSprite* menuSprite)
{
	Director::getInstance()->pushScene(ConfirmationMenu::create("Exit this level?", CC_CALLBACK_0(PauseMenu::onExitConfirm, this), nullptr));
}
