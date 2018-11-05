#include "PlayerPassBanner.h"

PlayerPassBanner* PlayerPassBanner::create()
{
	PlayerPassBanner* instance = new PlayerPassBanner();

	instance->autorelease();

	return instance;
}

PlayerPassBanner::PlayerPassBanner()
{
	this->playerPassBanner1 = Sprite::create(Resources::Minigames_Hexus_PlayerPassBanner);
	this->playerPassBanner2 = Sprite::create(Resources::Minigames_Hexus_PlayerPassBanner);

	this->setBannerText("YOU PASSED");

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

PlayerPassBanner::~PlayerPassBanner()
{
}

void PlayerPassBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerPassBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerPassBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::Pass && gameState->turn == GameState::Turn::Player && gameState->isPlayerPassCondition())
	{
		this->flashBanner();
	}
}
