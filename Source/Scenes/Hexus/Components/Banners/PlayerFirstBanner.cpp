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

void PlayerFirstBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerFirstBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->previousStateType == GameState::CoinFlip && gameState->round == 0 && gameState->turn == GameState::Turn::Player)
	{
		this->flashBanner();
	}
}
