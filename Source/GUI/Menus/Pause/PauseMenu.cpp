#include "PauseMenu.h"

PauseMenu * PauseMenu::create()
{
	PauseMenu* pauseMenu = new PauseMenu();

	pauseMenu->autorelease();

	return pauseMenu;
}

PauseMenu::PauseMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background = Sprite::create(Resources::Menus_PauseMenu_Background);
	this->pauseWindow = Sprite::create(Resources::Menus_PauseMenu_PauseMenu);

	this->fireflies = ParticleSystemQuad::create(Resources::Particles_Fireflies2);

	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->pauseWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->fireflies->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(this->background);
	this->addChild(this->fireflies);
	this->addChild(this->pauseWindow);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();
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

void PauseMenu::OnExitGame(Ref* pSender)
{
	// Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	//// EventCustom customEndEvent("game_scene_close_event");
	//// _eventDispatcher->dispatchEvent(&customEndEvent);
}