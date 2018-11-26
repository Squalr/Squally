#include "DrawBanner.h"

DrawBanner* DrawBanner::create()
{
	DrawBanner* instance = new DrawBanner();

	instance->autorelease();

	return instance;
}

DrawBanner::DrawBanner()
{
	this->defeatBanner1 = Sprite::create(HexusResources::RoundBanner);
	this->defeatBanner2 = Sprite::create(HexusResources::RoundBanner);

	this->setBannerText("DRAW!");

	this->addBannerChild(this->defeatBanner1);
	this->addBannerChild(this->defeatBanner2);
}

DrawBanner::~DrawBanner()
{
}

void DrawBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->defeatBanner1->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter - Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
	this->defeatBanner2->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::bannerIconOffset, visibleSize.height / 2.0f + 320.0f);
}

void DrawBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void DrawBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::GameEnd && gameState->enemyLosses == 2 && gameState->playerLosses == 2)
	{
		this->showBanner();
	}
	else
	{
		this->hideBanner();
	}
}
