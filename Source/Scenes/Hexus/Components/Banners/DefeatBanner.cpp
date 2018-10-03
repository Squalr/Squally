#include "DefeatBanner.h"

DefeatBanner* DefeatBanner::create()
{
	DefeatBanner* instance = new DefeatBanner();

	instance->autorelease();

	return instance;
}

DefeatBanner::DefeatBanner()
{
	this->setBannerText("DEFEAT!");
}

DefeatBanner::~DefeatBanner()
{
}

void DefeatBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void DefeatBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::GameEnd || gameState->playerLosses >= 2)
	{
		this->showBanner();
	}
	else if (gameState->previousStateType == GameState::GameEnd)
	{
		this->hideBanner();
	}
}
