#include "VictoryBanner.h"

VictoryBanner* VictoryBanner::create()
{
	VictoryBanner* instance = new VictoryBanner();

	instance->autorelease();

	return instance;
}

VictoryBanner::VictoryBanner()
{
	this->setBannerText("VICTORY!");
}

VictoryBanner::~VictoryBanner()
{
}

void VictoryBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void VictoryBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void VictoryBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::GameEnd && gameState->enemyLosses >= 2)
	{
		this->showBanner();
	}
	else
	{
		this->hideBanner();
	}
}
