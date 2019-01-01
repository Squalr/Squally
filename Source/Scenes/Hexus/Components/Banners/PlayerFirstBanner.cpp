#include "PlayerFirstBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Banners/PlayerFirst.h"

using namespace cocos2d;

PlayerFirstBanner* PlayerFirstBanner::create()
{
	PlayerFirstBanner* instance = new PlayerFirstBanner();

	instance->autorelease();

	return instance;
}

PlayerFirstBanner::PlayerFirstBanner()
{
	this->playerBanner1 = Sprite::create(HexusResources::PlayerBanner);
	this->playerBanner2 = Sprite::create(HexusResources::PlayerBanner);

	this->setBannerText(Strings::Hexus_Banners_PlayerFirst::create());

	this->addBannerChild(this->playerBanner1);
	this->addBannerChild(this->playerBanner2);
}

PlayerFirstBanner::~PlayerFirstBanner()
{
}

void PlayerFirstBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerFirstBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerFirstBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	// First mover banner does not apply to games with initial states
	if (gameState->opponentData->stateOverride != nullptr)
	{
		return;
	}

	if (!gameState->isRepeatingSameTurn && gameState->stateType == GameState::StateType::PlayerTurnStart && gameState->roundNumber == 0 && gameState->turnNumber == 0)
	{
		this->flashBanner();
	}
}
