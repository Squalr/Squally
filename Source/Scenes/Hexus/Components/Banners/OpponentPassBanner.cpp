#include "OpponentPassBanner.h"

OpponentPassBanner* OpponentPassBanner::create()
{
	OpponentPassBanner* instance = new OpponentPassBanner();

	instance->autorelease();

	return instance;
}

OpponentPassBanner::OpponentPassBanner()
{
	this->opponentPassBanner1 = Sprite::create(Resources::Minigames_Hexus_EnemyPassBanner);
	this->opponentPassBanner2 = Sprite::create(Resources::Minigames_Hexus_EnemyPassBanner);

	this->setBannerText("OPPONENT PASSED");

	this->addBannerChild(this->opponentPassBanner1);
	this->addBannerChild(this->opponentPassBanner2);
}

OpponentPassBanner::~OpponentPassBanner()
{
}

void OpponentPassBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->opponentPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->opponentPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void OpponentPassBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void OpponentPassBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::Pass && gameState->turn == GameState::Turn::Enemy)
	{
		this->flashBanner();
	}
}
