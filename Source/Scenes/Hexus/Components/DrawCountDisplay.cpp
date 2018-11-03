#include "DrawCountDisplay.h"

DrawCountDisplay* DrawCountDisplay::create()
{
	DrawCountDisplay* instance = new DrawCountDisplay();

	instance->autorelease();

	return instance;
}

DrawCountDisplay::DrawCountDisplay()
{
	this->drawCountSprite = Sprite::create(Resources::Minigames_Hexus_CardDrawIconSmall);
	this->drawCountLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->enemyDrawCountSprite = Sprite::create(Resources::Minigames_Hexus_CardDrawIconSmall);
	this->enemyDrawCountLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	this->drawCountLabel->enableOutline(Color4B::BLACK, 4);
	//this->drawCountSprite->setOpacity(0);
	this->enemyDrawCountLabel->enableOutline(Color4B::BLACK, 4);
	this->enemyDrawCountSprite->setOpacity(0);

	this->drawCountSprite->addChild(this->drawCountLabel);
	this->addChild(this->drawCountSprite);
	this->enemyDrawCountSprite->addChild(this->enemyDrawCountLabel);
	this->addChild(this->enemyDrawCountSprite);
}

DrawCountDisplay::~DrawCountDisplay()
{
}

void DrawCountDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->drawCountSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + 144.0f);
	this->drawCountLabel->setPosition(Vec2(this->drawCountSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));
	this->enemyDrawCountSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY - 144.0f);
	this->enemyDrawCountLabel->setPosition(Vec2(this->enemyDrawCountSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));
}

void DrawCountDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void DrawCountDisplay::onStateChange(GameState* gameState)
{
	ComponentBase::onStateChange(gameState);

	// Hide on last round -- there will be no next turn, thus draw count is irrelevent
	if (gameState->playerLosses >= 1 && gameState->enemyLosses >= 1)
	{
		this->drawCountSprite->runAction(FadeTo::create(0.25f, 0));
		this->enemyDrawCountSprite->runAction(FadeTo::create(0.25f, 0));

		return;
	}

	this->drawCountLabel->setString(std::to_string(gameState->playerCardsDrawnNextRound));
	this->enemyDrawCountLabel->setString(std::to_string(gameState->enemyCardsDrawnNextRound));

	switch (gameState->stateType)
	{
		case GameState::PlayerTurnStart:
		{
			if (!gameState->enemyLastStanded)
			{
				this->drawCountSprite->runAction(FadeTo::create(0.25f, 255));
			}

			break;
		}
		case GameState::OpponentTurnStart:
		{
			if (!gameState->playerLastStanded)
			{
				this->enemyDrawCountSprite->runAction(FadeTo::create(0.25f, 255));
			}

			break;
		}
		case GameState::TurnEnd:
		{
			// this->drawCountSprite->runAction(FadeTo::create(0.25f, 0));
			this->enemyDrawCountSprite->runAction(FadeTo::create(0.25f, 0));
			break;
		}
	}
}
