#include "PlayerTurnBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

PlayerTurnBanner* PlayerTurnBanner::create()
{
	PlayerTurnBanner* instance = new PlayerTurnBanner();

	instance->autorelease();

	return instance;
}

PlayerTurnBanner::PlayerTurnBanner()
{
	this->playerBanner1 = Sprite::create(HexusResources::PlayerBanner);
	this->playerBanner2 = Sprite::create(HexusResources::PlayerBanner);

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

void PlayerTurnBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	// Only show after the first turn -- first turn is reserved for PlayerFirstBanner
	if (!gameState->isRepeatingSameTurn && gameState->stateType == GameState::StateType::PlayerTurnStart && (gameState->roundNumber >= 1 || gameState->turnNumber >= 1))
	{
		this->flashBanner();
	}
}
