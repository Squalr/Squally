#include "OpponentFirstBanner.h"

OpponentFirstBanner* OpponentFirstBanner::create()
{
	OpponentFirstBanner* instance = new OpponentFirstBanner();

	instance->autorelease();

	return instance;
}

OpponentFirstBanner::OpponentFirstBanner()
{
	this->setBannerText("OPPONENT GOES FIRST");
}

OpponentFirstBanner::~OpponentFirstBanner()
{
}

void OpponentFirstBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void OpponentFirstBanner::onStateChange(GameState* gameState)
{
	if (gameState->stateType == GameState::GameEnd || gameState->enemyLosses >= 2)
	{
		this->showBanner();
	}
}
