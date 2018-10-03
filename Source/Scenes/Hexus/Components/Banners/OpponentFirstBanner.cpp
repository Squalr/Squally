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

void OpponentFirstBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void OpponentFirstBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->previousStateType == GameState::CoinFlip && gameState->round == 0 && gameState->turn == GameState::Turn::Enemy)
	{
		this->flashBanner();
	}
}
