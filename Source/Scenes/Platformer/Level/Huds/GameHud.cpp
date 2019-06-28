#include "GameHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
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
	this->statsBars = StatsBars::create();

	this->statsBars->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->statsBars->setVisible(false);

	this->addChild(this->statsBars);
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
}

void GameHud::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudTrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->statsBars->setStatsTarget(args->entity);

			this->statsBars->setVisible(true);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudUntrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->statsBars->setStatsTarget(nullptr);

			this->statsBars->setVisible(false);
		}
	}));
}

void GameHud::update(float dt)
{
	super::update(dt);
}
