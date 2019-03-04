#include "DrawCountDisplay.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/DrawToolTip.h"
#include "Strings/Generics/Constant.h"

using namespace cocos2d;

DrawCountDisplay* DrawCountDisplay::create()
{
	DrawCountDisplay* instance = new DrawCountDisplay();

	instance->autorelease();

	return instance;
}

DrawCountDisplay::DrawCountDisplay()
{
	this->drawCountSprite = ClickableNode::create(HexusResources::CardDrawIconSmall, HexusResources::CardDrawIconSmall);
	this->drawCountLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Generics_Constant::create());
	this->enemyDrawCountSprite = Sprite::create(HexusResources::CardDrawIconSmall);
	this->enemyDrawCountLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Generics_Constant::create());

	this->deckDrawCountMouseOverPanel = LayerColor::create(Color4B::BLACK, 320.0f, 96.0f);
	this->deckDrawCountCardMouseOverLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hexus_DrawToolTip::create());

	this->deckDrawCountCardMouseOverLabel->setDimensions(320.0f - 16.0f, 0.0f);

	this->drawCountLabel->enableOutline(Color4B::BLACK, 4);
	this->enemyDrawCountLabel->enableOutline(Color4B::BLACK, 4);

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

void DrawCountDisplay::onEnter()
{
	ComponentBase::onEnter();

	this->deckDrawCountMouseOverPanel->setOpacity(0);
	this->deckDrawCountCardMouseOverLabel->setOpacity(0);
	this->enemyDrawCountSprite->setOpacity(0);
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
		visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY - this->deckDrawCountMouseOverPanel->getContentSize().height / 2.0f + 96.0f
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

	this->drawCountLabel->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->playerCardsDrawnNextRound)));
	this->enemyDrawCountLabel->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->enemyCardsDrawnNextRound)));

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
		default:
		case GameState::StateType::PlayerTurnStart:
		{
			if (!gameState->enemyPassed)
			{
				this->drawCountSprite->runAction(FadeTo::create(0.25f, 255));
			}

			break;
		}
		case GameState::StateType::OpponentTurnStart:
		{
			if (!gameState->playerPassed)
			{
				this->enemyDrawCountSprite->runAction(FadeTo::create(0.25f, 255));
			}

			break;
		}
		case GameState::StateType::TurnEnd:
		{
			// this->drawCountSprite->runAction(FadeTo::create(0.25f, 0));
			this->enemyDrawCountSprite->runAction(FadeTo::create(0.25f, 0));
			break;
		}
	}
}
