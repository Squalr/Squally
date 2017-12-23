#include "PauseMenu.h"

PauseMenu * PauseMenu::create()
{
	PauseMenu* pauseMenu = new PauseMenu();

	pauseMenu->autorelease();

	return pauseMenu;
}

PauseMenu::PauseMenu()
{
	this->mouse = Mouse::create();
	this->background = Sprite::create(Resources::Menus_PauseMenu_Background);
	this->pauseWindow = Sprite::create(Resources::Menus_PauseMenu_PauseMenu);
	this->resumeButton = MenuSprite::create(Resources::Menus_PauseMenu_ResumeButton, Resources::Menus_PauseMenu_ResumeButtonHover, Resources::Menus_PauseMenu_ResumeButtonClick);
	this->optionsButton = MenuSprite::create(Resources::Menus_PauseMenu_OptionsButton, Resources::Menus_PauseMenu_OptionsButtonHover, Resources::Menus_PauseMenu_OptionsButtonClick);
	this->exitToTitleButton = MenuSprite::create(Resources::Menus_PauseMenu_QuitButton, Resources::Menus_PauseMenu_QuitButtonHover, Resources::Menus_PauseMenu_QuitButtonClick);

	this->fireflies = ParticleSystemQuad::create(Resources::Particles_Fireflies2);

	this->resumeButton->SetClickCallback(CC_CALLBACK_1(PauseMenu::OnResumeClick, this));
	this->optionsButton->SetClickCallback(CC_CALLBACK_1(PauseMenu::OnOptionsClick, this));
	this->exitToTitleButton->SetClickCallback(CC_CALLBACK_1(PauseMenu::OnExitToTitleClick, this));

	this->addChild(this->background);
	this->addChild(this->fireflies);
	this->addChild(this->pauseWindow);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitToTitleButton);
	this->addChild(this->mouse);

	this->InitializeListeners();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::onEnter()
{
	Scene::onEnter();

	this->InitializePositions();
}

void PauseMenu::InitializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->fireflies->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->pauseWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->resumeButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 128.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 0.0f));
	this->exitToTitleButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 180.0f));
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
