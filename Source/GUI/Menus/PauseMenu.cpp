#include "PauseMenu.h"
#include "Resources.h"

PauseMenu::PauseMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* label = Label::createWithTTF("Paused", Resources::Fonts_Marker_Felt, 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	MenuItemImage* closeItem = MenuItemImage::create(Resources::CloseNormal, Resources::CloseSelected, CC_CALLBACK_1(PauseMenu::OnExitGame, this));

	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = origin.y + closeItem->getContentSize().height / 2;

	closeItem->setPosition(Vec2(x, y));

	// create menu, it's an autorelease object
	Menu* menu = Menu::create(closeItem, NULL);

	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	this->InitializeListeners();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PauseMenu::OnKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void PauseMenu::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
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