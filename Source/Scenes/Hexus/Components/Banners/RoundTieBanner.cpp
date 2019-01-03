#include "RoundTieBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Banners/RoundTied.h"

using namespace cocos2d;

RoundTieBanner* RoundTieBanner::create()
{
	RoundTieBanner* instance = new RoundTieBanner();

	instance->autorelease();

	return instance;
}

RoundTieBanner::RoundTieBanner()
{
	this->playerPassBanner1 = Sprite::create(HexusResources::RoundBanner);
	this->playerPassBanner2 = Sprite::create(HexusResources::RoundBanner);

	this->setBannerText(Strings::Hexus_Banners_RoundTied::create());

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

RoundTieBanner::~RoundTieBanner()
{
}

void RoundTieBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void RoundTieBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);

	if (gameState->stateType == GameState::StateType::RoundEnd && gameState->isRoundTied())
	{
		this->flashBanner();
	}
}

void RoundTieBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);
}
