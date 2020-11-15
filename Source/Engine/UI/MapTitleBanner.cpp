#include "MapTitleBanner.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/HUD/Hud.h"

using namespace cocos2d;

const float MapTitleBanner::BannerBarHeight = 8.0f;

MapTitleBanner* MapTitleBanner::create(LocalizedString* bannerString)
{
	MapTitleBanner* instance = new MapTitleBanner(bannerString);

	instance->autorelease();

	return instance;
}

MapTitleBanner::MapTitleBanner(LocalizedString* bannerString) : super()
{
	this->bannerString = bannerString;
	this->hud = Hud::create();
	this->contentNode = Node::create();
	this->bannerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::S1, this->bannerString);
	this->bannerBarTop = DrawNode::create();
	this->bannerBarBottom = DrawNode::create();
	this->hasRelocated = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->bannerBarTop->drawSolidRect(-Vec2(visibleSize.width / 2.0f, MapTitleBanner::BannerBarHeight / 2.0f), Vec2(visibleSize.width / 2.0f, MapTitleBanner::BannerBarHeight / 2.0f), Color4F::WHITE);
	this->bannerBarBottom->drawSolidRect(-Vec2(visibleSize.width / 2.0f, MapTitleBanner::BannerBarHeight / 2.0f), Vec2(visibleSize.width / 2.0f, MapTitleBanner::BannerBarHeight / 2.0f), Color4F::WHITE);

	this->bannerLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->bannerLabel->enableShadow(Color4B::BLACK, Size(4.0f, -4.0f), 0);

	this->contentNode->addChild(this->bannerBarTop);
	this->contentNode->addChild(this->bannerBarBottom);
	this->contentNode->addChild(this->bannerLabel);
	this->hud->addChild(this->contentNode);
	this->addChild(hud);
}

MapTitleBanner::~MapTitleBanner()
{
}

void MapTitleBanner::onEnter()
{
	super::onEnter();
	
	this->defer([=]()
	{
		if (!this->hasRelocated)
		{
			// Move the UI elements to the top-most layer
			ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(
				this->hud
			));
			this->hasRelocated = true;
		}
	});

	this->hud->setOpacity(255);
	this->hud->runAction(Sequence::create(
		DelayTime::create(1.75f),
		FadeTo::create(0.5f, 0),
		nullptr
	));
}

void MapTitleBanner::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->bannerBarTop->setPosition(Vec2(0.0f, 320.0f + 64.0f));
	this->bannerBarBottom->setPosition(Vec2(0.0f, 320.0f - 64.0f));
	this->bannerLabel->setPosition(Vec2(0.0f, 320.0f));
}
