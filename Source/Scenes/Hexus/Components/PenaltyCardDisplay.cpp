#include "PenaltyCardDisplay.h"

PenaltyCardDisplay* PenaltyCardDisplay::create()
{
	PenaltyCardDisplay* instance = new PenaltyCardDisplay();

	instance->autorelease();

	return instance;
}

PenaltyCardDisplay::PenaltyCardDisplay()
{
	this->penaltyCardSprite = Sprite::create(Resources::Minigames_Hexus_PenaltyCardsIcon);
	this->penaltyCardLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->penaltyParticles = ParticleSystemQuad::create(Resources::Particles_PurpleAura);

	this->enemyPenaltyCardSprite = Sprite::create(Resources::Minigames_Hexus_PenaltyCardsIcon);
	this->enemyPenaltyCardLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->enemyPenaltyParticles = ParticleSystemQuad::create(Resources::Particles_PurpleAura);

	this->penaltyCardLabel->enableOutline(Color4B::BLACK, 4);
	this->penaltyCardSprite->setOpacity(0);
	this->penaltyParticles->setVisible(false);
	this->enemyPenaltyCardLabel->enableOutline(Color4B::BLACK, 4);
	this->enemyPenaltyCardSprite->setOpacity(0);
	this->enemyPenaltyParticles->setVisible(false);

	this->penaltyCardSprite->addChild(this->penaltyCardLabel);
	this->addChild(this->penaltyParticles);
	this->addChild(this->penaltyCardSprite);
	this->enemyPenaltyCardSprite->addChild(this->enemyPenaltyCardLabel);
	this->addChild(this->enemyPenaltyParticles);
	this->addChild(this->enemyPenaltyCardSprite);
}

PenaltyCardDisplay::~PenaltyCardDisplay()
{
}

void PenaltyCardDisplay::onEnter()
{
	ComponentBase::onEnter();

	this->penaltyParticles->start();
	this->enemyPenaltyParticles->start();
}

void PenaltyCardDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->penaltyParticles->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + 144.0f);
	this->penaltyCardSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + 144.0f);
	this->penaltyCardLabel->setPosition(Vec2(this->penaltyCardSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));

	this->enemyPenaltyParticles->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY - 144.0f);
	this->enemyPenaltyCardSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY - 144.0f);
	this->enemyPenaltyCardLabel->setPosition(Vec2(this->enemyPenaltyCardSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));
}

void PenaltyCardDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PenaltyCardDisplay::onStateChange(GameState* gameState)
{
	ComponentBase::onStateChange(gameState);

	this->penaltyCardLabel->setString(std::to_string(gameState->penaltyCardsPlayed));
	this->enemyPenaltyCardLabel->setString(std::to_string(gameState->penaltyCardsPlayed));

	switch (gameState->stateType)
	{
		case GameState::PlayerTurnStart:
		{
			if (gameState->enemyLastStanded)
			{
				this->penaltyCardSprite->runAction(FadeTo::create(0.25f, 255));
				this->penaltyParticles->start();
				this->penaltyParticles->setVisible(true);
			}

			break;
		}
		case GameState::OpponentTurnStart:
		{
			if (gameState->playerLastStanded)
			{
				this->enemyPenaltyCardSprite->runAction(FadeTo::create(0.25f, 255));
				this->enemyPenaltyParticles->start();
				this->enemyPenaltyParticles->setVisible(true);
			}

			break;
		}
		case GameState::RoundEnd:
		{
			this->penaltyCardSprite->runAction(FadeTo::create(0.25f, 0));
			this->penaltyParticles->stop();
			this->penaltyParticles->setVisible(false);

			this->enemyPenaltyCardSprite->runAction(FadeTo::create(0.25f, 0));
			this->enemyPenaltyParticles->stop();
			this->enemyPenaltyParticles->setVisible(false);

			break;
		}
	}
}
