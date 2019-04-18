#include "GameHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Platformer/Level/Huds/Components/CurrencyDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/RuneBar.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"

using namespace cocos2d;

GameHud* GameHud::create()
{
	GameHud* instance = new GameHud();

	instance->autorelease();

	return instance;
}

GameHud::GameHud()
{
	this->currencyDisplay = CurrencyDisplay::create();
	this->runeBar = RuneBar::create();
	this->statsBars = StatsBars::create();
	this->controlsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create("WASD/Space to move, TAB to view assembly. Demo build!"));

	this->statsBars->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->controlsLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->runeBar->setVisible(false);

	this->addChild(this->statsBars);
	this->addChild(this->runeBar);
	this->addChild(this->currencyDisplay);
	this->addChild(this->controlsLabel);
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
	this->runeBar->setPosition(24.0f + 0.0f, visibleSize.height - 64.0f - 88.0f);
	this->currencyDisplay->setPosition(24.0f + 112.0f, visibleSize.height - 64.0f - 88.0f);
	this->controlsLabel->setPosition(24.0f, 24.0f);
}

void GameHud::initializeListeners()
{
	super::initializeListeners();
}

void GameHud::update(float dt)
{
	super::update(dt);
}

CurrencyDisplay* GameHud::getCurrencyDisplay()
{
	return this->currencyDisplay;
}

RuneBar* GameHud::getRuneBar()
{
	return this->runeBar;
}

StatsBars* GameHud::getStatsBars()
{
	return this->statsBars;
}
