#include "ControlSacrificeStaged.h"

ControlSacrificeStaged* ControlSacrificeStaged::create()
{
	ControlSacrificeStaged* controlSacrificeStaged = new ControlSacrificeStaged();

	controlSacrificeStaged->autorelease();

	return controlSacrificeStaged;
}

ControlSacrificeStaged::ControlSacrificeStaged()
{
	this->sacrificeStatus = Label::create("", Resources::Fonts_Montserrat_Medium, 28.0f);

	this->sacrificeStatus->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->sacrificeStatus->setTextColor(Color4B::WHITE);
	this->sacrificeStatus->enableOutline(Color4B::BLACK, 2);
	this->sacrificeStatus->setDimensions(Config::statusLabelWidth, 0.0f);
	this->sacrificeStatus->setOpacity(0);

	this->cancelButton = MenuSprite::create(Resources::Menus_Buttons_CancelV2Button, Resources::Menus_Buttons_CancelV2ButtonHover, Resources::Menus_Buttons_CancelV2ButtonClick);
	this->cancelButton->setCascadeOpacityEnabled(true);
	this->cancelButton->setOpacity(0.0f);
	this->cancelButton->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->sacrificeStatus);
	this->addChild(this->cancelButton);
}

ControlSacrificeStaged::~ControlSacrificeStaged()
{
}

void ControlSacrificeStaged::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ControlSacrificeStaged::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cancelButton->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::statusLabelWidth / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
	this->sacrificeStatus->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter - Config::statusLabelWidth / 2.0f - this->cancelButton->getContentSize().width / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
}

void ControlSacrificeStaged::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void ControlSacrificeStaged::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->stateType == GameState::StateType::ControlSacrificeStaged) {
		switch (gameState->turn)
		{
		case GameState::Turn::Player:
			this->initializeCallbacks(gameState);
			this->updateSacrificeStatus();
			break;
		case GameState::Turn::Enemy:
			this->aiPerformAction(gameState);
			break;
		}
	}
}

void ControlSacrificeStaged::initializeCallbacks(GameState* gameState)
{
	this->cancelButton->setClickCallback(CC_CALLBACK_1(ControlSacrificeStaged::onSacrificeCancel, this));

	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlSacrificeStaged::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(ControlSacrificeStaged::selectCard, this));

	gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));
	gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));
	gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));
	gameState->enemyBinaryCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));
	gameState->enemyDecimalCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));
	gameState->enemyHexCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));

	gameState->stagedSacrificeTargets->clear();
	gameState->stagedSacrifice->setFocusTint(Color3B::RED);
	gameState->stagedSacrifice->focus();
	gameState->stagedSacrifice->setMouseClickCallback(nullptr);
}

void ControlSacrificeStaged::aiPerformAction(GameState* gameState)
{

}

void ControlSacrificeStaged::selectCard(Card* card)
{
	// Unstage/deselect card if clicking the active card
	if (card == this->activeGameState->selectedCard)
	{
		this->activeGameState->selectedCard->stopAllActions();
		this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));
		GameState::updateState(this->activeGameState, GameState::StateType::ControlNeutral);
		return;
	}

	// Otherwise this is just a selection/re-staging of a new card
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));

	this->activeGameState->selectedCard = card;
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	// Transition to the selection state (re-initialize things)
	GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
}


void ControlSacrificeStaged::stageSacrificeTarget(Card* card)
{
	switch (this->activeGameState->selectedCard->cardData->cardType) {
	case CardData::CardType::Special_AND:
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
		if (this->activeGameState->stagedSacrificeTargets->find(card) == this->activeGameState->stagedSacrificeTargets->end())
		{
			card->focus();
			card->setFocusTint(Color3B::BLUE);
			this->activeGameState->stagedSacrificeTargets->insert(card);
		}
		else
		{

			card->unfocus();
			this->activeGameState->stagedSacrificeTargets->erase(this->activeGameState->stagedSacrificeTargets->find(card));
		}
		break;
	}

	switch (this->activeGameState->selectedCard->cardData->cardType) {
	case CardData::CardType::Special_AND:
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
		if (this->activeGameState->stagedSacrificeTargets->size() >= 2)
		{
			this->activeGameState->stagedSacrifice->unfocus();
			this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
			this->activeGameState->playerGraveyard->insertCardTop(this->activeGameState->selectedCard, true, Config::insertDelay);

			this->activeGameState->stagedSacrificeCardRow->removeCard(this->activeGameState->stagedSacrifice);
			this->activeGameState->playerGraveyard->insertCardTop(this->activeGameState->stagedSacrifice, true, Config::insertDelay);

			Card::Operation operation = Card::toOperation(this->activeGameState->selectedCard->cardData->cardType, this->activeGameState->stagedSacrifice->getAttack());

			for (auto it = this->activeGameState->stagedSacrificeTargets->begin(); it != this->activeGameState->stagedSacrificeTargets->end(); *it++)
			{
				Card* target = *it;

				target->addOperation(operation);
			}

			GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		}
		break;
	}

	this->updateSacrificeStatus();
}

void ControlSacrificeStaged::onSacrificeCancel(MenuSprite* menuSprite)
{
	// Deselect current card (by selecting the selected card)
	this->selectCard(this->activeGameState->selectedCard);

	this->updateSacrificeStatus();
}

void ControlSacrificeStaged::updateSacrificeStatus()
{
	if (this->activeGameState->turn != GameState::Turn::Player)
	{
		return;
	}

	switch (this->activeGameState->stateType)
	{
	case GameState::StateType::ControlSacrificeStaged:

		switch (this->activeGameState->selectedCard->cardData->cardType) {
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
			int remaining = 2 - this->activeGameState->stagedSacrificeTargets->size();

			if (remaining == 1)
			{
				this->sacrificeStatus->setString("Choose " + std::to_string(remaining) + " more target");
			}
			else
			{
				this->sacrificeStatus->setString("Choose " + std::to_string(remaining) + " more targets");
			}

			break;
		}

		this->sacrificeStatus->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
		break;
	default:
		this->sacrificeStatus->runAction(FadeTo::create(0.25f, 0));
		this->cancelButton->runAction(FadeTo::create(0.25f, 0));
	}
}
