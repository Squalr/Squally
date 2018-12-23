#include "StateAIDecideTarget.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/States/HexusAIHelper.h"

using namespace cocos2d;

StateAIDecideTarget* StateAIDecideTarget::create()
{
	StateAIDecideTarget* instance = new StateAIDecideTarget();

	instance->autorelease();

	return instance;
}

StateAIDecideTarget::StateAIDecideTarget() : StateBase(GameState::StateType::AIDecideTarget)
{
}

StateAIDecideTarget::~StateAIDecideTarget()
{
}

void StateAIDecideTarget::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateAIDecideTarget::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	// Unable to find a card to play (ie it would be disadvantageous to play any card for the opponent)
	if (gameState->selectedHandCard == nullptr)
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::Pass);
			}),
			nullptr
		));

		return;
	}

	switch (gameState->selectedHandCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
		{
			gameState->selectedRow = gameState->enemyBinaryCards;
			break;
		}
		case CardData::CardType::Decimal:
		{
			gameState->selectedRow = gameState->enemyDecimalCards;
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			gameState->selectedRow = gameState->enemyHexCards;
			break;
		}
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		{
			gameState->selectedRow = std::get<0>(gameState->cachedBestRowPlay);
			break;
		}
		case CardData::CardType::Special_MOV:
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
		{
			gameState->selectedSourceCard = std::get<0>(gameState->cachedBestSourceTargetPlay);
			gameState->selectedDestinationCard = std::get<1>(gameState->cachedBestSourceTargetPlay);
			break;
		}
		case CardData::CardType::Special_INV:
		{
			gameState->selectedDestinationCard = std::get<0>(gameState->cachedBestTargetPlay);

			break;
		}
		default:
		{
			break;
		}
	}

	this->runAction(Sequence::create(
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::PlayCard);
		}),
		nullptr
	));
}

void StateAIDecideTarget::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateAIDecideTarget::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
