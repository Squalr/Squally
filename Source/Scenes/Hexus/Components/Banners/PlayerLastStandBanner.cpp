#include "PlayerLastStandBanner.h"

PlayerLastStandBanner* PlayerLastStandBanner::create()
{
	PlayerLastStandBanner* instance = new PlayerLastStandBanner();

	instance->autorelease();

	return instance;
}

PlayerLastStandBanner::PlayerLastStandBanner()
{
	this->playerPassBanner1 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);
	this->playerPassBanner2 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);

	this->setBannerText("YOU PASSED");

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

PlayerLastStandBanner::~PlayerLastStandBanner()
{
}

void PlayerLastStandBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerLastStandBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerLastStandBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::LastStand && gameState->turn == GameState::Turn::Player)
	{
		this->flashBanner();
	}
}
