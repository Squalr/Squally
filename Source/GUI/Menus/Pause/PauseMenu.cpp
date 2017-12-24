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
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButton, Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);
	this->resumeButton = MenuSprite::create(Resources::Menus_PauseMenu_ResumeButton, Resources::Menus_PauseMenu_ResumeButtonHover, Resources::Menus_PauseMenu_ResumeButtonClick);
	this->optionsButton = MenuSprite::create(Resources::Menus_PauseMenu_OptionsButton, Resources::Menus_PauseMenu_OptionsButtonHover, Resources::Menus_PauseMenu_OptionsButtonClick);
	this->exitToTitleButton = MenuSprite::create(Resources::Menus_PauseMenu_QuitButton, Resources::Menus_PauseMenu_QuitButtonHover, Resources::Menus_PauseMenu_QuitButtonClick);

	this->resumeButton->SetClickCallback(CC_CALLBACK_1(PauseMenu::OnResumeClick, this));
	this->optionsButton->SetClickCallback(CC_CALLBACK_1(PauseMenu::OnOptionsClick, this));
	this->exitToTitleButton->SetClickCallback(CC_CALLBACK_1(PauseMenu::OnExitToTitleClick, this));

	this->closeButton->SetClickCallback(CC_CALLBACK_1(PauseMenu::OnCloseClick, this));
	this->closeButton->SetClickSound(Resources::Sounds_ClickBack1);

	this->addChild(this->background);
	this->addChild(this->pauseWindow);
	this->addChild(this->closeButton);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitToTitleButton);

	this->InitializeListeners();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::onEnter()
{
	FadeScene::onEnter();

	this->background->addChild(MenuBackground::ClaimInstance());

	this->InitializePositions();

	this->addChild(Mouse::claimInstance());
}

void PauseMenu::InitializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->pauseWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 136.0f, origin.y + visibleSize.height / 2 + 204.0f));
	this->resumeButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 128.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 0.0f));
	this->exitToTitleButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 180.0f));

	MenuBackground::GetInstance()->InitializePositions();
}

void PauseMenu::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PauseMenu::OnKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void PauseMenu::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->popScene();
		break;
	}
}

void PauseMenu::OnCloseClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();
}

void PauseMenu::OnResumeClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();
}

void PauseMenu::OnOptionsClick(MenuSprite* menuSprite)
{
	Director::getInstance()->pushScene(OptionsMenu::create());
}

void PauseMenu::OnExitToTitleClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popToSceneStackLevel(2);
}
