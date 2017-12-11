#include "OptionsMenu.h"

OptionsMenu::OptionsMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* label = Label::createWithTTF("Options", Resources::Fonts_Marker_Felt, 24);
	Menu* menu = Menu::create();

	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

	this->closeItem = MenuItemImage::create(Resources::CloseNormal, Resources::CloseSelected);
	this->closeItem->setPosition(Vec2(origin.x + visibleSize.width - this->closeItem->getContentSize().width / 2, origin.y + this->closeItem->getContentSize().height / 2));

	menu->setPosition(Vec2::ZERO);
	menu->addChild(this->closeItem);

	this->addChild(label);
	this->addChild(menu);
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();
}

void OptionsMenu::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(OptionsMenu::OnKeyPressed, this);

	this->closeItem->setCallback(CC_CALLBACK_1(OptionsMenu::OnExitGame, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void OptionsMenu::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->popScene();
		break;
	}
}

void OptionsMenu::OnExitGame(Ref* pSender)
{
	// Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	//// EventCustom customEndEvent("game_scene_close_event");
	//// _eventDispatcher->dispatchEvent(&customEndEvent);
}