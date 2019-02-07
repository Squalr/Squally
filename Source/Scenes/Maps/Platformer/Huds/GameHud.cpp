#include "GameHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Maps/Platformer/Huds/Components/HackableBar.h"
#include "Scenes/Maps/Platformer/Huds/Components/StatsBars.h"

using namespace cocos2d;

GameHud* GameHud::create()
{
	GameHud* instance = new GameHud();

	instance->autorelease();

	return instance;
}

GameHud::GameHud()
{
	this->hackableBar = HackableBar::create();
	this->statsBars = StatsBars::create();

	this->statsBars->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->statsBars);
	this->addChild(this->hackableBar);
}

GameHud::~GameHud()
{
}

void GameHud::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void GameHud::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->statsBars->setPosition(24.0f, visibleSize.height - 64.0f);
	this->hackableBar->setPosition(24.0f + 88.0f, visibleSize.height - 64.0f - 96.0f);
}

void GameHud::initializeListeners()
{
	super::initializeListeners();
}

void GameHud::update(float dt)
{
	super::update(dt);
}

HackableBar* GameHud::getHackableBar()
{
	return this->hackableBar;
}

StatsBars* GameHud::getStatsBars()
{
	return this->statsBars;
}
