#include "DrawBanner.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

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

	this->setBannerText(Strings::Hexus_Banners_Draw::create());

	this->addBannerChild(this->defeatBanner1);
	this->addBannerChild(this->defeatBanner2);
}

DrawBanner::~DrawBanner()
{
}

void DrawBanner::initializePositions()
{
	super::initializePositions();

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
	super::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::GameEnd && gameState->enemyLosses == 2 && gameState->playerLosses == 2)
	{
		this->showBanner();
	}
	else
	{
		this->hideBanner();
	}
}
