#include "Banners.h"

Banners* Banners::create()
{
	Banners* banners = new Banners();

	banners->autorelease();

	return banners;
}

Banners::Banners()
{
	this->statusBanner = LayerColor::create(Color4B(0, 0, 0, 127), 1920.0f, 144.0f);
	this->statusLabel = Label::create("", Resources::Fonts_Montserrat_Medium, 48.0f);

	this->statusBanner->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusBanner->setOpacity(0);
	this->statusLabel->setOpacity(0);

	this->addChild(this->statusBanner);
	this->addChild(this->statusLabel);
}

Banners::~Banners()
{
}

void Banners::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void Banners::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->statusBanner->setPosition(0.0f, visibleSize.height / 2.0f - this->statusBanner->getContentSize().height / 2 + 320.0f);
	this->statusLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f);
}

void Banners::initializeListeners()
{
}

void Banners::onStateChange(GameState* gameState)
{
	this->updateBanner(gameState);
}

void Banners::updateBanner(GameState* gameState)
{
	this->statusLabel->setString(gameState->bannerMessage);

	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));

	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 127),
		DelayTime::create(Config::bannerDisplayDuration),
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));
}
