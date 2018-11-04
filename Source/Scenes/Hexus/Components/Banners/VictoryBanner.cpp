#include "VictoryBanner.h"

VictoryBanner* VictoryBanner::create()
{
	VictoryBanner* instance = new VictoryBanner();

	instance->autorelease();

	return instance;
}

VictoryBanner::VictoryBanner()
{
	this->victoryBanner1 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);
	this->victoryBanner2 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);

	this->setBannerText("VICTORY!");

	this->addBannerChild(this->victoryBanner1);
	this->addBannerChild(this->victoryBanner2);
}

VictoryBanner::~VictoryBanner()
{
}

void VictoryBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->victoryBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->victoryBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void VictoryBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void VictoryBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::GameEnd && gameState->enemyLosses >= 2 && gameState->playerLosses < 2)
	{
		this->showBanner();
	}
	else
	{
		this->hideBanner();
	}
}
