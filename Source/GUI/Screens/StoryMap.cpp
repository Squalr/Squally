#include "StoryMap.h"

StoryMap::StoryMap()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->titleLabel = new MenuLabel("Level Select", Resources::Fonts_Marker_Felt, 16);
	this->infoLabel = new MenuLabel("Level 1", Resources::Fonts_Marker_Felt, 8);
	this->background = Sprite::create(Resources::GUI_WorldMaps_StoryMap);
	this->mouse = new Mouse();

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->titleLabel->GetSize().height));
	this->infoLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->infoLabel->GetSize().height - 24));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(this->background);
	this->addChild(this->titleLabel);
	this->addChild(this->infoLabel);
	this->addChild(this->mouse);

	this->InitializeListeners();
}

StoryMap::~StoryMap()
{
	delete(this->mouse);
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
