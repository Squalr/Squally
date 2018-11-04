#include "DefeatBanner.h"

DefeatBanner* DefeatBanner::create()
{
	DefeatBanner* instance = new DefeatBanner();

	instance->autorelease();

	return instance;
}

DefeatBanner::DefeatBanner()
{
	this->defeatBanner1 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);
	this->defeatBanner2 = Sprite::create(Resources::Minigames_Hexus_EnemyBanner);

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

	if (gameState->stateType == GameState::GameEnd && gameState->playerLosses >= 2)
	{
		this->showBanner();
	}
	else
	{
		this->hideBanner();
	}
}
