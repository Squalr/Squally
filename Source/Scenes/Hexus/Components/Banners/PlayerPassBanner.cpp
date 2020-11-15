#include "PlayerPassBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"

#include "Strings/Strings.h"

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
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter - HexusConfig::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter + HexusConfig::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void PlayerPassBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PlayerPassBanner::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::Pass && gameState->turn == GameState::Turn::Player && gameState->isPlayerPassCondition())
	{
		this->flashBanner();
	}
}
