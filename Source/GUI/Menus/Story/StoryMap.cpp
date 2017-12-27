#include "StoryMap.h"

StoryMap * StoryMap::create()
{
	StoryMap* storyMap = new StoryMap();

	storyMap->autorelease();

	return storyMap;
}

StoryMap::StoryMap()
{
	this->titleLabel = MenuLabel::create("Level Select", Resources::Fonts_Marker_Felt, this->titleFontSize);
	this->infoLabel = MenuLabel::create("Level 1", Resources::Fonts_Marker_Felt, this->infoFontSize);
	this->background = Sprite::create(Resources::Menus_WorldMaps_StoryMap);

	this->addChild(this->background);
	this->addChild(this->titleLabel);
	this->addChild(this->infoLabel);

	this->initializeListeners();
}

StoryMap::~StoryMap()
{
}

void StoryMap::onEnter()
{
	FadeScene::onEnter();

	this->initializePositions();

	this->addChild(Mouse::claimInstance());
}

void StoryMap::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->titleLabel->getContentSize().height / 2));
	this->infoLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->infoLabel->getContentSize().height / 2 - 48));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
}

void StoryMap::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(StoryMap::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void StoryMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->popScene();
		break;
	}
}
