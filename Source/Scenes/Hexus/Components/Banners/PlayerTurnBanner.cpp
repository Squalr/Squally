#include "PlayerTurnBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"

#include "Strings/Strings.h"

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

	this->setBannerText(Strings::Hexus_Banners_PlayerTurn::create());

	this->addBannerChild(this->playerBanner1);
	this->addBannerChild(this->playerBanner2);
}

PlayerTurnBanner::~PlayerTurnBanner()
{
}

void PlayerTurnBanner::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerBanner1->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter - HexusConfig::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerBanner2->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter + HexusConfig::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerTurnBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerTurnBanner::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	// Only show after the first turn -- first turn is reserved for PlayerFirstBanner
	if (!gameState->isRepeatingSameTurn && gameState->stateType == GameState::StateType::PlayerTurnStart && (gameState->roundNumber >= 1 || gameState->turnNumber >= 1))
	{
		this->flashBanner();
	}
}
