#include "PlayerPassBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Banners/PlayerPassed.h"

using namespace cocos2d;

PlayerPassBanner* PlayerPassBanner::create()
{
	PlayerPassBanner* instance = new PlayerPassBanner();

	instance->autorelease();

	return instance;
}

PlayerPassBanner::PlayerPassBanner()
{
	this->playerPassBanner1 = Sprite::create(HexusResources::PlayerPassBanner);
	this->playerPassBanner2 = Sprite::create(HexusResources::PlayerPassBanner);

	this->setBannerText(Strings::Hexus_Banners_PlayerPassed::create());

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

PlayerPassBanner::~PlayerPassBanner()
{
}

void PlayerPassBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerPassBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerPassBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::Pass && gameState->turn == GameState::Turn::Player && gameState->isPlayerPassCondition())
	{
		this->flashBanner();
	}
}
