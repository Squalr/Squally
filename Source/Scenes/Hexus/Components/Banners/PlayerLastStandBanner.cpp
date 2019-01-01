#include "PlayerLastStandBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Banners/LastStand.h"

using namespace cocos2d;

PlayerLastStandBanner* PlayerLastStandBanner::create()
{
	PlayerLastStandBanner* instance = new PlayerLastStandBanner();

	instance->autorelease();

	return instance;
}

PlayerLastStandBanner::PlayerLastStandBanner()
{
	this->playerPassBanner1 = Sprite::create(HexusResources::PlayerBanner);
	this->playerPassBanner2 = Sprite::create(HexusResources::PlayerBanner);

	this->setBannerText(Strings::Hexus_Banners_LastStand::create());

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

PlayerLastStandBanner::~PlayerLastStandBanner()
{
}

void PlayerLastStandBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerLastStandBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerLastStandBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::Pass && gameState->turn == GameState::Turn::Player && gameState->isPlayerLastStandCondition())
	{
		this->flashBanner();
	}
}
