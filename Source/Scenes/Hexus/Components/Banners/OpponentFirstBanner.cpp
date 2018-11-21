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

void OpponentFirstBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	// First mover banner does not apply to games with initial states
	if (gameState->opponentData->stateOverride != nullptr)
	{
		return;
	}

	if (!gameState->isRepeatingSameTurn && gameState->stateType == GameState::OpponentTurnStart && gameState->roundNumber == 0 && gameState->turnNumber == 0)
	{
		this->flashBanner();
	}
}
