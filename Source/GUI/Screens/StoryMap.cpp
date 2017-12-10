#include "StoryMap.h"
#include "Resources.h"
#include "../Mouse.h"

StoryMap::StoryMap()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* titleLabel = Label::createWithTTF("Squalr Tutorial", Resources::Fonts_Marker_Felt, 24);
	Label* startLabel = Label::createWithTTF("Press Enter to Start", Resources::Fonts_Marker_Felt, 16);

	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titleLabel->getContentSize().height));
	startLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - startLabel->getContentSize().height / 2));

	this->addChild(Sprite::create(Resources::GUI_TitleScreen_TitleScreen));
	this->addChild(titleLabel);
	this->addChild(startLabel);
	this->addChild(new Mouse());

	this->InitializeListeners();
}

StoryMap::~StoryMap()
{
}

void StoryMap::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(StoryMap::OnKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void StoryMap::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
		break;
	}
}
