#include "VictoryBanner.h"

#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

VictoryBanner* VictoryBanner::create()
{
	VictoryBanner* instance = new VictoryBanner();

	instance->autorelease();

	return instance;
}

VictoryBanner::VictoryBanner()
{
	this->victoryBanner1 = Sprite::create(HexusResources::PlayerBanner);
	this->victoryBanner2 = Sprite::create(HexusResources::PlayerBanner);

	this->setBannerText("VICTORY!");

	this->addBannerChild(this->victoryBanner1);
	this->addBannerChild(this->victoryBanner2);
}

VictoryBanner::~VictoryBanner()
{
}

void VictoryBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->victoryBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->victoryBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void VictoryBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void VictoryBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::GameEnd && gameState->enemyLosses >= 2 && gameState->playerLosses < 2)
	{
		this->showBanner();
	}
	else
	{
		this->hideBanner();
	}
}
