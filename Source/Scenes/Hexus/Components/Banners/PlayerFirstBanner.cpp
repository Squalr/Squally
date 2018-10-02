#include "PlayerFirstBanner.h"

PlayerFirstBanner* PlayerFirstBanner::create()
{
	PlayerFirstBanner* instance = new PlayerFirstBanner();

	instance->autorelease();

	return instance;
}

PlayerFirstBanner::PlayerFirstBanner()
{
	this->setBannerText("YOU GO FIRST");
}

PlayerFirstBanner::~PlayerFirstBanner()
{
}

void PlayerFirstBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void PlayerFirstBanner::onStateChange(GameState* gameState)
{
	if (gameState->stateType == GameState::GameEnd || gameState->enemyLosses >= 2)
	{
		this->showBanner();
	}
}
