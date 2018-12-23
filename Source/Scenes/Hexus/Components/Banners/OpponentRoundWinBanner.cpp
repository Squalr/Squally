#include "OpponentRoundWinBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

OpponentRoundWinBanner* OpponentRoundWinBanner::create()
{
	OpponentRoundWinBanner* instance = new OpponentRoundWinBanner();

	instance->autorelease();

	return instance;
}

OpponentRoundWinBanner::OpponentRoundWinBanner()
{
	this->playerPassBanner1 = Sprite::create(HexusResources::EnemyBanner);
	this->playerPassBanner2 = Sprite::create(HexusResources::EnemyBanner);

	this->setBannerText("OPPONENT WINS THE ROUND");

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

OpponentRoundWinBanner::~OpponentRoundWinBanner()
{
}

void OpponentRoundWinBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void OpponentRoundWinBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);

	if (gameState->stateType == GameState::StateType::RoundEnd && gameState->isEnemyWinningRound())
	{
		this->flashBanner();
	}
}

void OpponentRoundWinBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);
}
