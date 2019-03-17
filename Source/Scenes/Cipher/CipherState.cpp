#include "CipherState.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Utils/StrUtils.h"

#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CipherState::requestStateUpdateEvent = "EVENT_HEXUS_REQUEST_UPDATE_STATE";
const std::string CipherState::beforeStateUpdateEvent = "EVENT_HEXUS_BEFORE_UPDATE_STATE";
const std::string CipherState::onStateUpdateEvent = "EVENT_HEXUS_ON_UPDATE_STATE";

CipherState* CipherState::create()
{
	CipherState* instance = new CipherState();

	instance->autorelease();

	return instance;
}

CipherState::CipherState()
	: stateType(StateType::EmptyState),
	updateStateCallback(nullptr)
{
	this->playerDeck = Deck::create();
	this->playerHand = CardRow::create(true);
	this->playerGraveyard = Deck::create();
	this->playerBinaryCards = CardRow::create(true);
	this->playerDecimalCards = CardRow::create(true);
	this->playerHexCards = CardRow::create(true);

	this->enemyDeck = Deck::create();
	this->enemyHand = CardRow::create(false);
	this->enemyGraveyard = Deck::create();
	this->enemyBinaryCards = CardRow::create(false);
	this->enemyDecimalCards = CardRow::create(false);
	this->enemyHexCards = CardRow::create(false);

	this->enemyHand->setVisible(false);
	this->playerHand->setRowWidth(Config::handWidth, 0.0f);
	this->enemyHand->setRowWidth(Config::enemyHandWidth, 0.0f);

	this->addChild(this->enemyGraveyard);
	this->addChild(this->enemyDeck);
	this->addChild(this->enemyHexCards);
	this->addChild(this->enemyDecimalCards);
	this->addChild(this->enemyBinaryCards);
	this->addChild(this->enemyHand);

	this->addChild(this->playerGraveyard);
	this->addChild(this->playerDeck);
	this->addChild(this->playerHexCards);
	this->addChild(this->playerDecimalCards);
	this->addChild(this->playerBinaryCards);
	this->addChild(this->playerHand);
}

CipherState::~CipherState()
{
}

void CipherState::initializePositions()
{
	SmartNode::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyGraveyard->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::graveyardOffsetY);
	this->playerGraveyard->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::graveyardOffsetY);

	this->playerDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY);
	this->enemyDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY);

	this->playerHand->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - Config::handOffsetY);
	this->playerBinaryCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY);
	this->playerDecimalCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY);
	this->playerHexCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY);

	this->enemyHand->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::handOffsetY + 256.0f);
	this->enemyBinaryCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY);
	this->enemyDecimalCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY);
	this->enemyHexCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY);
}

void CipherState::updateState(CipherState* gameState, StateType newState)
{
	gameState->previousStateType = gameState->stateType;
	gameState->stateType = newState;
	gameState->clearInteraction();

	switch (newState)
	{
		case StateType::GameStart:
		{
			gameState->gameStartTime = std::chrono::high_resolution_clock::now();
			break;
		}
		case StateType::GameEnd:
		{
			gameState->gameEndTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = gameState->gameEndTime - gameState->gameStartTime;
			gameState->gameDurationInSeconds = (int)(elapsed.count());
			break;
		}
		default:
		{
			break;
		}
	}

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CipherState::requestStateUpdateEvent, gameState);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CipherState::beforeStateUpdateEvent, gameState);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CipherState::onStateUpdateEvent, gameState);
}

void CipherState::clearInteraction()
{

}
