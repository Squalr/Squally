#include "ChallengeBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ChallengeBanner* ChallengeBanner::create()
{
	ChallengeBanner* instance = new ChallengeBanner();

	instance->autorelease();

	return instance;
}

ChallengeBanner::ChallengeBanner()
{
	this->roundBanner1 = Sprite::create(HexusResources::RoundBanner);
	this->roundBanner2 = Sprite::create(HexusResources::RoundBanner);

	this->setBannerText(Strings::Hexus_Banners_Challenge::create());

	this->addBannerChild(this->roundBanner1);
	this->addBannerChild(this->roundBanner2);
}

ChallengeBanner::~ChallengeBanner()
{
}

void ChallengeBanner::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->roundBanner1->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter - HexusConfig::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->roundBanner2->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter + HexusConfig::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void ChallengeBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void ChallengeBanner::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	if (gameState->showChallengeBanner && gameState->stateType == GameState::StateType::LoadInitialState)
	{
		this->flashBanner();
	}
}
