#include "RoundTieBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"

#include "Strings/Strings.h"

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
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter - HexusConfig::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter + HexusConfig::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
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
	super::onAnyStateChange(gameState);
}
