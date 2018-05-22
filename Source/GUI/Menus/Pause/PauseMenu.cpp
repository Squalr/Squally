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

	this->addChild(this->background);
	this->addChild(this->pauseWindow);
	this->addChild(this->closeButton);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);

	// TEMP: Level editor
	Node* label = Label::create("Level editor", Resources::Fonts_Montserrat_Medium, 24);
	Node* labelHover = Label::create("Level editor", Resources::Fonts_Montserrat_Medium, 24);
	Node* labelClick = Label::create("Level editor", Resources::Fonts_Montserrat_Medium, 24);
	labelHover->setColor(Color3B::YELLOW);
	labelClick->setColor(Color3B::YELLOW);
	this->levelEditorButton = MenuSprite::create(label, labelHover, labelClick);
	this->addChild(this->levelEditorButton);

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
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->resumeButton, delay, duration);
	GameUtils::fadeInObject(this->optionsButton, delay, duration);
	GameUtils::fadeInObject(this->levelEditorButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);

	this->background->addChild(MenuBackground::claimInstance());

	this->initializePositions();
	this->initializeListeners();

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
	this->levelEditorButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 96.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 180.0f));

	MenuBackground::getInstance()->initializePositions();
}

void PauseMenu::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(PauseMenu::onKeyPressed, this);

	this->resumeButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onResumeClick, this));
	this->optionsButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onOptionsClick, this));
	this->levelEditorButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onLevelEditorClick, this));
	this->exitButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onExitClick, this));

	this->closeButton->setClickCallback(CC_CALLBACK_1(PauseMenu::onCloseClick, this));
	this->closeButton->setClickSound(Resources::Sounds_ClickBack1);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void PauseMenu::onLevelPause(EventCustom* eventCustom)
{
	PauseEvents::PauseEventArgs* args = (PauseEvents::PauseEventArgs*)(eventCustom->getUserData());

	this->currentLevelFile = args->currentLevelFile;
	this->pauseLocation = args->pauseLocation;

	NavigationEvents::navigate(NavigationEvents::GameScreen::Pause);
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

void PauseMenu::onLevelEditorClick(MenuSprite* menuSprite)
{
	NavigationEvents::loadLevelEditor(this->currentLevelFile, this->pauseLocation);
}

void PauseMenu::onExitClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateConfirm("Exit this level?", CC_CALLBACK_0(PauseMenu::onExitConfirm, this), nullptr);
}
