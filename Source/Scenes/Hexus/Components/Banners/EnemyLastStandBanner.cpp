#include "EnemyLastStandBanner.h"

EnemyLastStandBanner* EnemyLastStandBanner::create()
{
	EnemyLastStandBanner* instance = new EnemyLastStandBanner();

	instance->autorelease();

	return instance;
}

EnemyLastStandBanner::EnemyLastStandBanner()
{
	this->playerPassBanner1 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);
	this->playerPassBanner2 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);

	this->setBannerText("YOU PASSED");

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

EnemyLastStandBanner::~EnemyLastStandBanner()
{
}

void EnemyLastStandBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void EnemyLastStandBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void EnemyLastStandBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::LastStand && gameState->turn == GameState::Turn::Enemy)
	{
		this->flashBanner();
	}
}
