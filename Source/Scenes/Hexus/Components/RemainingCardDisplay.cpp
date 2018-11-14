#include "RemainingCardDisplay.h"

RemainingCardDisplay* RemainingCardDisplay::create()
{
	RemainingCardDisplay* instance = new RemainingCardDisplay();

	instance->autorelease();

	return instance;
}

RemainingCardDisplay::RemainingCardDisplay()
{
	this->particles = ParticleSystemQuad::create(Resources::Particles_Hexus_BlueAura);
	this->remainingCardSprite = MenuSprite::create(Resources::Minigames_Hexus_RemainingCardsIcon, Resources::Minigames_Hexus_RemainingCardsIcon);
	this->remainingCardLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->enemyRemainingCardSprite = Sprite::create(Resources::Minigames_Hexus_RemainingCardsIcon);
	this->enemyRemainingCardLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	this->remainingCardMouseOverPanel = LayerColor::create(Color4B::BLACK, 320.0f, 96.0f);
	this->remainingCardMouseOverLabel = Label::create(
		Localization::resolveString("The number of cards that can be played this turn"),
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont())
	);

	this->remainingCardMouseOverLabel->setDimensions(320.0f - 16.0f, 0.0f);

	this->remainingCardLabel->enableOutline(Color4B::BLACK, 4);
	this->enemyRemainingCardLabel->enableOutline(Color4B::BLACK, 4);

	this->remainingCardSprite->addChild(this->remainingCardLabel);
	this->addChild(this->particles);
	this->addChild(this->remainingCardSprite);
	this->enemyRemainingCardSprite->addChild(this->enemyRemainingCardLabel);
	this->addChild(this->enemyRemainingCardSprite);
	this->addChild(this->remainingCardMouseOverPanel);
	this->addChild(this->remainingCardMouseOverLabel);
}

RemainingCardDisplay::~RemainingCardDisplay()
{
}

void RemainingCardDisplay::onEnter()
{
	ComponentBase::onEnter();

	this->remainingCardMouseOverPanel->setOpacity(0);
	this->remainingCardMouseOverLabel->setOpacity(0);
	this->particles->setVisible(false);
	this->remainingCardSprite->setOpacity(0);
	this->enemyRemainingCardSprite->setOpacity(0);
}

void RemainingCardDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float spriteOffsetY = 144.0f;

	this->particles->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY);
	this->remainingCardSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY);
	this->remainingCardLabel->setPosition(Vec2(16.0f, -this->remainingCardSprite->getContentSize().height / 2.0f + 16.0f));
	this->enemyRemainingCardSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY - spriteOffsetY);
	this->enemyRemainingCardLabel->setPosition(Vec2(this->enemyRemainingCardSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));

	this->remainingCardMouseOverPanel->setPosition(
		visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX - this->remainingCardMouseOverPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY - this->remainingCardMouseOverPanel->getContentSize().height / 2.0 + 96.0f
	);
	this->remainingCardMouseOverLabel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY + 96.0f);
}

void RemainingCardDisplay::onRemaningCardDisplayMouseOver()
{
	this->remainingCardMouseOverPanel->setOpacity(196);
	this->remainingCardMouseOverLabel->setOpacity(255);
}

void RemainingCardDisplay::onRemaningCardDisplayMouseOut()
{
	this->remainingCardMouseOverPanel->setOpacity(0);
	this->remainingCardMouseOverLabel->setOpacity(0);
}

void RemainingCardDisplay::enableCardDisplayInteraction()
{
	this->particles->setVisible(true);
	this->remainingCardSprite->setMouseOverCallback(CC_CALLBACK_0(RemainingCardDisplay::onRemaningCardDisplayMouseOver, this));
	this->remainingCardSprite->setMouseOutCallback(CC_CALLBACK_0(RemainingCardDisplay::onRemaningCardDisplayMouseOut, this));
}

void RemainingCardDisplay::disableCardDisplayInteraction()
{
	this->particles->setVisible(false);
	this->remainingCardSprite->setMouseOverCallback(nullptr);
	this->remainingCardSprite->setMouseOutCallback(nullptr);
	this->onRemaningCardDisplayMouseOut();
}

void RemainingCardDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void RemainingCardDisplay::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

	if (gameState->enemyPassed || gameState->playerPassed)
	{
		wchar_t const * utf16_string = L"\u221E";
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
		std::string infinitySymbol = convert.to_bytes(utf16_string);

		this->remainingCardLabel->setString(infinitySymbol);
		this->enemyRemainingCardLabel->setString(infinitySymbol);
	}
	else
	{
		this->remainingCardLabel->setString(std::to_string(gameState->playableCardsThisTurn));
		this->enemyRemainingCardLabel->setString(std::to_string(gameState->playableCardsThisTurn));
	}

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			this->enemyRemainingCardLabel->setString(std::to_string(0));
			break;
		}
		case GameState::Turn::Enemy:
		{
			this->remainingCardLabel->setString(std::to_string(0));
			break;
		}
		default:
		{
			break;
		}
	}

	switch (gameState->stateType)
	{
		case GameState::StateType::Neutral:
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
		{
			this->enableCardDisplayInteraction();

			break;
		}
		default:
		{
			this->disableCardDisplayInteraction();

			break;
		}
	}

	switch (gameState->stateType)
	{
		case GameState::PlayerTurnStart:
		{
			this->remainingCardSprite->runAction(FadeTo::create(0.25f, 255));
			break;
		}
		case GameState::OpponentTurnStart:
		{
			this->enemyRemainingCardSprite->runAction(FadeTo::create(0.25f, 255));
			break;
		}
		case GameState::TurnEnd:
		{
			//this->remainingCardSprite->runAction(FadeTo::create(0.25f, 0));
			this->enemyRemainingCardSprite->runAction(FadeTo::create(0.25f, 0));
			break;
		}
	}
}
