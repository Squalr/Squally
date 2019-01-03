#include "OpponentLastStandBanner.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Banners/LastStand.h"

using namespace cocos2d;

OpponentLastStandBanner* OpponentLastStandBanner::create()
{
	OpponentLastStandBanner* instance = new OpponentLastStandBanner();

	instance->autorelease();

	return instance;
}

OpponentLastStandBanner::OpponentLastStandBanner()
{
	this->playerPassBanner1 = Sprite::create(HexusResources::EnemyBanner);
	this->playerPassBanner2 = Sprite::create(HexusResources::EnemyBanner);

	this->setBannerText(Strings::Hexus_Banners_LastStand::create());

	this->addBannerChild(this->playerPassBanner1);
	this->addBannerChild(this->playerPassBanner2);
}

OpponentLastStandBanner::~OpponentLastStandBanner()
{
}

void OpponentLastStandBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerPassBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->playerPassBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void OpponentLastStandBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void OpponentLastStandBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::Pass && gameState->turn == GameState::Turn::Enemy && gameState->isEnemyLastStandCondition())
	{
		this->flashBanner();
	}
}
