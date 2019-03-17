#include "PlayerRoundWinBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Banners/PlayerRoundWin.h"

using namespace cocos2d;

PlayerRoundWinBanner* PlayerRoundWinBanner::create()
{
	PlayerRoundWinBanner* instance = new PlayerRoundWinBanner();

	instance->autorelease();

	return instance;
}

PlayerRoundWinBanner::PlayerRoundWinBanner()
{
	this->playerPassBanner1 = Sprite::create(HexusResources::PlayerBanner);
	this->playerPassBanner2 = Sprite::create(HexusResources::PlayerBanner);

	this->setBannerText(Strings::Hexus_Banners_PlayerRoundWin::create());

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

PlayerRoundWinBanner::~PlayerRoundWinBanner()
{
}

void PlayerRoundWinBanner::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerRoundWinBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);

	if (gameState->stateType == GameState::StateType::RoundEnd && gameState->isPlayerWinningRound())
	{
		this->flashBanner();
	}
}

void PlayerRoundWinBanner::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}
