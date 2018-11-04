#include "PlayerRoundWinBanner.h"

PlayerRoundWinBanner* PlayerRoundWinBanner::create()
{
	PlayerRoundWinBanner* instance = new PlayerRoundWinBanner();

	instance->autorelease();

	return instance;
}

PlayerRoundWinBanner::PlayerRoundWinBanner()
{
	this->playerPassBanner1 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);
	this->playerPassBanner2 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);

	this->setBannerText("YOU WIN THE ROUND");

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

PlayerRoundWinBanner::~PlayerRoundWinBanner()
{
}

void PlayerRoundWinBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerRoundWinBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);

	if (gameState->stateType == GameState::RoundEnd && gameState->isPlayerWinningRound())
	{
		this->flashBanner();
	}
}

void PlayerRoundWinBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);
}
