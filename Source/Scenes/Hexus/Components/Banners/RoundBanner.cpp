#include "RoundBanner.h"

RoundBanner* RoundBanner::create()
{
	RoundBanner* instance = new RoundBanner();

	instance->autorelease();

	return instance;
}

RoundBanner::RoundBanner()
{
	this->roundBanner1 = Sprite::create(Resources::Minigames_Hexus_RoundBanner);
	this->roundBanner2 = Sprite::create(Resources::Minigames_Hexus_RoundBanner);

	this->addBannerChild(this->roundBanner1);
	this->addBannerChild(this->roundBanner2);
}

RoundBanner::~RoundBanner()
{
}

void RoundBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->roundBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->roundBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void RoundBanner::onStateChange(GameState* gameState)
{
	if (gameState->stateType == GameState::RoundStart)
	{
		this->setBannerText(gameState->round >= 2 ? "FINAL ROUND" : "NEXT ROUND");
	}
}
