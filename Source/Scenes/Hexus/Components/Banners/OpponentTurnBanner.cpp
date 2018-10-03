#include "OpponentTurnBanner.h"

OpponentTurnBanner* OpponentTurnBanner::create()
{
	OpponentTurnBanner* instance = new OpponentTurnBanner();

	instance->autorelease();

	return instance;
}

OpponentTurnBanner::OpponentTurnBanner()
{
	this->enemyBanner1 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);
	this->enemyBanner2 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);

	this->setBannerText("OPPONENT'S TURN");

	this->addBannerChild(this->enemyBanner1);
	this->addBannerChild(this->enemyBanner2);
}

OpponentTurnBanner::~OpponentTurnBanner()
{
}

void OpponentTurnBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->enemyBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void OpponentTurnBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void OpponentTurnBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::OpponentTurnStart && gameState->round > 0)
	{
		this->flashBanner();
	}
}
