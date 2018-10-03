#include "PlayerTurnBanner.h"

PlayerTurnBanner* PlayerTurnBanner::create()
{
	PlayerTurnBanner* instance = new PlayerTurnBanner();

	instance->autorelease();

	return instance;
}

PlayerTurnBanner::PlayerTurnBanner()
{
	this->playerBanner1 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);
	this->playerBanner2 = Sprite::create(Resources::Minigames_Hexus_PlayerBanner);

	this->setBannerText("YOUR TURN");

	this->addBannerChild(this->playerBanner1);
	this->addBannerChild(this->playerBanner2);
}

PlayerTurnBanner::~PlayerTurnBanner()
{
}

void PlayerTurnBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerTurnBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerTurnBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::PlayerTurnStart && gameState->round > 0)
	{
		this->flashBanner();
	}
}
