#include "GameHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Huds/Components/IqEqDisplay.h"
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
	this->iqEqDisplay = IqEqDisplay::create();
	this->runeBar = RuneBar::create();
	this->statsBars = StatsBars::create();

	this->statsBars->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->statsBars->setVisible(false);
	this->runeBar->setVisible(false);
	this->iqEqDisplay->setVisible(false);

	this->addChild(this->statsBars);
	this->addChild(this->runeBar);
	this->addChild(this->iqEqDisplay);
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

	static const Vec2 offset = Vec2(24.0f, -96.0f);
	
	this->statsBars->setPosition(offset.x, visibleSize.height + offset.y);
	this->runeBar->setPosition(offset.x + 306.0f, visibleSize.height + offset.y + 36.0f);
	this->iqEqDisplay->setPosition(offset.x + 64.0f, visibleSize.height + offset.y - 32.0f);
}

void GameHud::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudTrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{

			this->getIqEqDisplay()->setStatsTarget(static_cast<Squally*>(args->entity));
			this->getRuneBar()->setStatsTarget(args->entity);
			this->getStatsBars()->setStatsTarget(args->entity);

			this->statsBars->setVisible(true);
			this->runeBar->setVisible(true);
			this->iqEqDisplay->setVisible(true);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudUntrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->getIqEqDisplay()->setStatsTarget(nullptr);
			this->getRuneBar()->setStatsTarget(nullptr);
			this->getStatsBars()->setStatsTarget(nullptr);

			this->statsBars->setVisible(false);
			this->runeBar->setVisible(false);
			this->iqEqDisplay->setVisible(false);
		}
	}));
}

void GameHud::update(float dt)
{
	super::update(dt);
}

IqEqDisplay* GameHud::getIqEqDisplay()
{
	return this->iqEqDisplay;
}

RuneBar* GameHud::getRuneBar()
{
	return this->runeBar;
}

StatsBars* GameHud::getStatsBars()
{
	return this->statsBars;
}
