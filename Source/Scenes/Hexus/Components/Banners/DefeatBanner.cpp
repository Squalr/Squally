#include "DefeatBanner.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

DefeatBanner* DefeatBanner::create()
{
	DefeatBanner* instance = new DefeatBanner();

	instance->autorelease();

	return instance;
}

DefeatBanner::DefeatBanner()
{
	this->defeatBanner1 = Sprite::create(HexusResources::EnemyBanner);
	this->defeatBanner2 = Sprite::create(HexusResources::EnemyBanner);

	this->setBannerText("DEFEAT!");

	this->addBannerChild(this->defeatBanner1);
	this->addBannerChild(this->defeatBanner2);
}

DefeatBanner::~DefeatBanner()
{
}

void DefeatBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->defeatBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->defeatBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void DefeatBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void DefeatBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::GameEnd && gameState->enemyLosses < 2 && gameState->playerLosses >= 2)
	{
		this->showBanner();
	}
	else
	{
		this->hideBanner();
	}
}
