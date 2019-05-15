#include "GameHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
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
	this->controlsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(""));

	this->statsBars->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->controlsLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->statsBars->setVisible(false);
	this->runeBar->setVisible(false);
	this->currencyDisplay->setVisible(false);

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

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudTrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->getCurrencyDisplay()->setCurrencyInventory(args->entity->getCurrencyInventory());
			this->getRuneBar()->setStatsTarget(args->entity);
			this->getStatsBars()->setStatsTarget(args->entity);

			this->statsBars->setVisible(true);
			this->runeBar->setVisible(true);
			this->currencyDisplay->setVisible(true);
		}
	}));
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
