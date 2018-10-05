#include "OpponentFirstBanner.h"

OpponentFirstBanner* OpponentFirstBanner::create()
{
	OpponentFirstBanner* instance = new OpponentFirstBanner();

	instance->autorelease();

	return instance;
}

OpponentFirstBanner::OpponentFirstBanner()
{
	this->enemyBanner1 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);
	this->enemyBanner2 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);

	this->setBannerText("OPPONENT GOES FIRST");

	this->addBannerChild(this->enemyBanner1);
	this->addBannerChild(this->enemyBanner2);
}

OpponentFirstBanner::~OpponentFirstBanner()
{
}

void OpponentFirstBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->enemyBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void OpponentFirstBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void OpponentFirstBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->previousStateType == GameState::CoinFlip && gameState->turnNumber == 0 && gameState->turn == GameState::Turn::Enemy)
	{
		this->flashBanner();
	}
}
