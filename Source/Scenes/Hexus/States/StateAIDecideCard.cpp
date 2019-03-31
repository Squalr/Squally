#include "StateAIDecideCard.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/States/HexusAIHelper.h"

using namespace cocos2d;

StateAIDecideCard* StateAIDecideCard::create()
{
	StateAIDecideCard* instance = new StateAIDecideCard();

	instance->autorelease();

	return instance;
}

StateAIDecideCard::StateAIDecideCard() : super(GameState::StateType::AIDecideCard)
{
}

StateAIDecideCard::~StateAIDecideCard()
{
}

void StateAIDecideCard::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateAIDecideCard::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	gameState->selectedHandCard = nullptr;

	switch (gameState->opponentData->strategy)
	{
		case HexusOpponentData::Strategy::StrongestCardsFirst:
		{
			this->decideCardStrongestFirst(gameState);
			break;
		}
		case HexusOpponentData::Strategy::WeakestCardsFirst:
		{
			this->decideCardWeakestFirst(gameState);
			break;
		}
		case HexusOpponentData::Strategy::Random:
		default:
		{
			this->decideCardRandom(gameState);
			break;
		}
	}

	this->runAction(Sequence::create(
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::AIDecideTarget);
		}),
		nullptr
	));
}

void StateAIDecideCard::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateAIDecideCard::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}

void StateAIDecideCard::decideCardRandom(GameState* gameState)
{
	gameState->enemyHand->shuffle();

	for (auto it = gameState->enemyHand->rowCards.begin(); it != gameState->enemyHand->rowCards.end(); it++)
	{
		Card* card = *it;

		switch (card->cardData->cardType)
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
			{
				gameState->selectedHandCard = card;

				break;
			}
			case CardData::CardType::Special_SHL:
			case CardData::CardType::Special_SHR:
			case CardData::CardType::Special_FLIP1:
			case CardData::CardType::Special_FLIP2:
			case CardData::CardType::Special_FLIP3:
			case CardData::CardType::Special_FLIP4:
			case CardData::CardType::Special_CLEAR:
			case CardData::CardType::Special_HEAL:
			case CardData::CardType::Special_POISON:
			case CardData::CardType::Special_DRANK:
			{
				std::tuple<CardRow*, int> bestPlay = HexusAIHelper::getBestRow(card, gameState);

				if (std::get<1>(bestPlay) > 0)
				{
					gameState->cachedBestRowPlay = bestPlay;
					gameState->selectedHandCard = card;

					return;
				}

				break;
			}
			case CardData::CardType::Special_MOV:
			case CardData::CardType::Special_AND:
			case CardData::CardType::Special_OR:
			case CardData::CardType::Special_XOR:
			case CardData::CardType::Special_ADD:
			case CardData::CardType::Special_SUB:
			{
				std::tuple<Card*, Card*, int> bestPlay = HexusAIHelper::getBestSourceAndTarget(card, gameState);

				if (std::get<2>(bestPlay) > 0)
				{
					gameState->cachedBestSourceTargetPlay = bestPlay;
					gameState->selectedHandCard = card;

					return;
				}

				break;
			}
			case CardData::CardType::Special_INV:
			{
				 std::tuple<Card*, int> bestPlay = HexusAIHelper::getBestTarget(card, gameState);

				if (std::get<1>(bestPlay) > 0)
				{
					gameState->cachedBestTargetPlay = bestPlay;
					gameState->selectedHandCard = card;

					return;
				}

				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void StateAIDecideCard::decideCardStrongestFirst(GameState* gameState)
{
	std::function<void()> chooseBestCallback = nullptr;
	int currentBestDiff = 0;

	for (auto it = gameState->enemyHand->rowCards.begin(); it != gameState->enemyHand->rowCards.end(); it++)
	{
		Card* card = *it;

		switch (card->cardData->cardType)
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
			{
				int diff = card->getAttack();

				if (diff < currentBestDiff)
				{
					chooseBestCallback = [gameState, card]()
					{
						gameState->selectedHandCard = card;
					};

					currentBestDiff = diff;
				}

				break;
			}
			case CardData::CardType::Special_SHL:
			case CardData::CardType::Special_SHR:
			case CardData::CardType::Special_FLIP1:
			case CardData::CardType::Special_FLIP2:
			case CardData::CardType::Special_FLIP3:
			case CardData::CardType::Special_FLIP4:
			case CardData::CardType::Special_CLEAR:
			case CardData::CardType::Special_HEAL:
			case CardData::CardType::Special_POISON:
			case CardData::CardType::Special_DRANK:
			{
				std::tuple<CardRow*, int> bestPlay = HexusAIHelper::getBestRow(card, gameState);
				int diff = std::get<1>(bestPlay);

				if (diff > currentBestDiff)
				{
					chooseBestCallback = [gameState, card, bestPlay]()
					{
						gameState->cachedBestRowPlay = bestPlay;
						gameState->selectedHandCard = card;
					};

					currentBestDiff = diff;
				}

				break;
			}
			case CardData::CardType::Special_MOV:
			case CardData::CardType::Special_AND:
			case CardData::CardType::Special_OR:
			case CardData::CardType::Special_XOR:
			case CardData::CardType::Special_ADD:
			case CardData::CardType::Special_SUB:
			{
				std::tuple<Card*, Card*, int> bestPlay = HexusAIHelper::getBestSourceAndTarget(card, gameState);
				int diff = std::get<2>(bestPlay);

				if (diff > currentBestDiff)
				{
					chooseBestCallback = [gameState, card, bestPlay]()
					{
						gameState->cachedBestSourceTargetPlay = bestPlay;
						gameState->selectedHandCard = card;
					};

					currentBestDiff = diff;
				}

				break;
			}
			case CardData::CardType::Special_INV:
			{
				std::tuple<Card*, int> bestPlay = HexusAIHelper::getBestTarget(card, gameState);
				int diff = std::get<1>(bestPlay);

				if (diff > currentBestDiff)
				{
					chooseBestCallback = [gameState, card, bestPlay]()
					{
						gameState->cachedBestTargetPlay = bestPlay;
						gameState->selectedHandCard = card;
					};

					currentBestDiff = diff;
				}

				break;
			}
			default:
			{
				break;
			}
		}
	}

	if (currentBestDiff > 0 && chooseBestCallback != nullptr)
	{
		chooseBestCallback();
	}
}

void StateAIDecideCard::decideCardWeakestFirst(GameState* gameState)
{
	std::function<void()> chooseBestCallback = nullptr;
	int currentBestDiff = std::numeric_limits<int>::max();

	for (auto it = gameState->enemyHand->rowCards.begin(); it != gameState->enemyHand->rowCards.end(); it++)
	{
		Card* card = *it;

		switch (card->cardData->cardType)
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
			{
				int diff = card->getAttack();

				if (diff < currentBestDiff && diff > 0)
				{
					chooseBestCallback = [gameState, card]()
					{
						gameState->selectedHandCard = card;
					};

					currentBestDiff = diff;
				}

				break;
			}
			case CardData::CardType::Special_SHL:
			case CardData::CardType::Special_SHR:
			case CardData::CardType::Special_FLIP1:
			case CardData::CardType::Special_FLIP2:
			case CardData::CardType::Special_FLIP3:
			case CardData::CardType::Special_FLIP4:
			case CardData::CardType::Special_CLEAR:
			case CardData::CardType::Special_HEAL:
			case CardData::CardType::Special_POISON:
			case CardData::CardType::Special_DRANK:
			{
				std::tuple<CardRow*, int> bestPlay = HexusAIHelper::getBestRow(card, gameState);
				int diff = std::get<1>(bestPlay);

				if (diff > currentBestDiff && diff > 0)
				{
					chooseBestCallback = [gameState, card, bestPlay]()
					{
						gameState->cachedBestRowPlay = bestPlay;
						gameState->selectedHandCard = card;
					};

					currentBestDiff = diff;
				}

				break;
			}
			case CardData::CardType::Special_MOV:
			case CardData::CardType::Special_AND:
			case CardData::CardType::Special_OR:
			case CardData::CardType::Special_XOR:
			case CardData::CardType::Special_ADD:
			case CardData::CardType::Special_SUB:
			{
				std::tuple<Card*, Card*, int> bestPlay = HexusAIHelper::getBestSourceAndTarget(card, gameState);
				int diff = std::get<2>(bestPlay);

				if (diff > currentBestDiff && diff > 0)
				{
					chooseBestCallback = [gameState, card, bestPlay]()
					{
						gameState->cachedBestSourceTargetPlay = bestPlay;
						gameState->selectedHandCard = card;
					};

					currentBestDiff = diff;
				}

				break;
			}
			case CardData::CardType::Special_INV:
			{
				std::tuple<Card*, int> bestPlay = HexusAIHelper::getBestTarget(card, gameState);
				int diff = std::get<1>(bestPlay);

				if (diff > currentBestDiff && diff > 0)
				{
					chooseBestCallback = [gameState, card, bestPlay]()
					{
						gameState->cachedBestTargetPlay = bestPlay;
						gameState->selectedHandCard = card;
					};

					currentBestDiff = diff;
				}

				break;
			}
			default:
			{
				break;
			}
		}
	}

	if (currentBestDiff > 0 && chooseBestCallback != nullptr)
	{
		chooseBestCallback();
	}
}
