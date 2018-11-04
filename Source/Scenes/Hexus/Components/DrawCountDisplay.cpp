#include "DrawCountDisplay.h"

DrawCountDisplay* DrawCountDisplay::create()
{
	DrawCountDisplay* instance = new DrawCountDisplay();

	instance->autorelease();

	return instance;
}

DrawCountDisplay::DrawCountDisplay()
{
	this->drawCountSprite = MenuSprite::create(Resources::Minigames_Hexus_CardDrawIconSmall, Resources::Minigames_Hexus_CardDrawIconSmall, Resources::Minigames_Hexus_CardDrawIconSmall);
	this->drawCountLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->enemyDrawCountSprite = Sprite::create(Resources::Minigames_Hexus_CardDrawIconSmall);
	this->enemyDrawCountLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	LayerColor* deckDrawCountMouseOverPanel;
	Label* deckDrawCountCardMouseOverLabel;

	this->deckDrawCountMouseOverPanel = LayerColor::create(Color4B::BLACK, 320.0f, 96.0f);
	this->deckDrawCountCardMouseOverLabel = Label::create(
		Localization::resolveString("The number of cards that will be drawn next round"),
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont())
	);

	this->deckDrawCountMouseOverPanel->setOpacity(0);
	this->deckDrawCountCardMouseOverLabel->setOpacity(0);
	this->deckDrawCountCardMouseOverLabel->setDimensions(320.0f - 16.0f, 0.0f);

	this->drawCountLabel->enableOutline(Color4B::BLACK, 4);
	//this->drawCountSprite->setOpacity(0);
	this->enemyDrawCountLabel->enableOutline(Color4B::BLACK, 4);
	this->enemyDrawCountSprite->setOpacity(0);

	this->drawCountSprite->addChild(this->drawCountLabel);
	this->addChild(this->drawCountSprite);
	this->enemyDrawCountSprite->addChild(this->enemyDrawCountLabel);
	this->addChild(this->enemyDrawCountSprite);
	this->addChild(this->deckDrawCountMouseOverPanel);
	this->addChild(this->deckDrawCountCardMouseOverLabel);
}

DrawCountDisplay::~DrawCountDisplay()
{
}

void DrawCountDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float spriteOffsetY = 144.0f;

	this->drawCountSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY);
	this->drawCountLabel->setPosition(Vec2(16.0f, -this->drawCountSprite->getContentSize().height / 2.0f + 16.0f));
	this->enemyDrawCountSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY - spriteOffsetY);
	this->enemyDrawCountLabel->setPosition(Vec2(this->enemyDrawCountSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));

	const float panelXOffset = -72.0f;

	this->deckDrawCountMouseOverPanel->setPosition(
		visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - this->deckDrawCountMouseOverPanel->getContentSize().width / 2.0f + panelXOffset,
		visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY - this->deckDrawCountMouseOverPanel->getContentSize().height / 2.0 + 96.0f
	);
	this->deckDrawCountCardMouseOverLabel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX + panelXOffset, visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY + 96.0f);
}

void DrawCountDisplay::onDrawCountDisplayMouseOver()
{
	this->deckDrawCountMouseOverPanel->setOpacity(196);
	this->deckDrawCountCardMouseOverLabel->setOpacity(255);
}

void DrawCountDisplay::onDrawCountDisplayMouseOut()
{
	this->deckDrawCountMouseOverPanel->setOpacity(0);
	this->deckDrawCountCardMouseOverLabel->setOpacity(0);
}

void DrawCountDisplay::enableDrawCountDisplayInteraction()
{
	this->drawCountSprite->setMouseOverCallback(CC_CALLBACK_0(DrawCountDisplay::onDrawCountDisplayMouseOver, this));
	this->drawCountSprite->setMouseOutCallback(CC_CALLBACK_0(DrawCountDisplay::onDrawCountDisplayMouseOut, this));
}

void DrawCountDisplay::disableDrawCountDisplayInteraction()
{
	this->drawCountSprite->setMouseOverCallback(nullptr);
	this->drawCountSprite->setMouseOutCallback(nullptr);
	this->onDrawCountDisplayMouseOut();
}

void DrawCountDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void DrawCountDisplay::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

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
		case GameState::StateType::Neutral:
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
		{
			this->enableDrawCountDisplayInteraction();

			break;
		}
		default:
		{
			this->disableDrawCountDisplayInteraction();

			break;
		}
	}

	switch (gameState->stateType)
	{
		case GameState::PlayerTurnStart:
		{
			if (!gameState->enemyPassed)
			{
				this->drawCountSprite->runAction(FadeTo::create(0.25f, 255));
			}

			break;
		}
		case GameState::OpponentTurnStart:
		{
			if (!gameState->playerPassed)
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
