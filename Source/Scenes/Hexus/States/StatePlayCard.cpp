#include "StatePlayCard.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Sound/SoundManager.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardEffects.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

StatePlayCard* StatePlayCard::create()
{
	StatePlayCard* instance = new StatePlayCard();

	instance->autorelease();

	return instance;
}

StatePlayCard::StatePlayCard() : super(GameState::StateType::PlayCard)
{
}

StatePlayCard::~StatePlayCard()
{
}

void StatePlayCard::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StatePlayCard::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	if (gameState->selectedHandCard == nullptr)
	{
		this->passFromError(gameState);
		return;
	}

	CardRow* selfHand = nullptr;
	CardRow* selfBinaryRow = nullptr;
	CardRow* selfDecimalRow = nullptr;
	CardRow* selfHexRow = nullptr;
	Deck* selfGraveyard = nullptr;
	Deck* selfDeck = nullptr;

	CardRow* otherHand = nullptr;
	CardRow* otherBinaryRow = nullptr;
	CardRow* otherDecimalRow = nullptr;
	CardRow* otherHexRow = nullptr;
	Deck* otherGraveyard = nullptr;
	Deck* otherDeck = nullptr;

	bool playedPeekCard = false;

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			selfHand = gameState->playerHand;
			selfBinaryRow = gameState->playerBinaryCards;
			selfDecimalRow = gameState->playerDecimalCards;
			selfHexRow = gameState->playerHexCards;
			selfGraveyard = gameState->playerGraveyard;
			selfDeck = gameState->playerDeck;

			otherHand = gameState->enemyHand;
			otherBinaryRow = gameState->enemyBinaryCards;
			otherDecimalRow = gameState->enemyDecimalCards;
			otherHexRow = gameState->enemyHexCards;
			otherGraveyard = gameState->enemyGraveyard;
			otherDeck = gameState->enemyDeck;
			break;
		}
		case GameState::Turn::Enemy:
		{
			selfHand = gameState->enemyHand;
			selfBinaryRow = gameState->enemyBinaryCards;
			selfDecimalRow = gameState->enemyDecimalCards;
			selfHexRow = gameState->enemyHexCards;
			selfGraveyard = gameState->enemyGraveyard;
			selfDeck = gameState->enemyDeck;

			otherHand = gameState->playerHand;
			otherBinaryRow = gameState->playerBinaryCards;
			otherDecimalRow = gameState->playerDecimalCards;
			otherHexRow = gameState->playerHexCards;
			otherGraveyard = gameState->playerGraveyard;
			otherDeck = gameState->playerDeck;
			break;
		}
		default:
		{
			this->passFromError(gameState);
			return;
		}
	}

	switch (gameState->selectedHandCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
		case CardData::CardType::Decimal:
		case CardData::CardType::Hexidecimal:
		{
			if (gameState->selectedRow == nullptr)
			{
				this->passFromError(gameState);
				return;
			}

			// Draw card effect for decimal 0 card
			if (gameState->selectedHandCard->cardData->cardKey == CardKeys::Decimal0)
			{
				selfHand->insertCard(selfDeck->drawCard(), gameState->turn == GameState::Turn::Player ? Config::insertDelay : 0.0f);
			}

			selfHand->removeCard(gameState->selectedHandCard);
			gameState->selectedRow->insertCard(gameState->selectedHandCard, Config::insertDelay);

			// Horde effect for hex 1 card
			if (gameState->selectedHandCard->cardData->cardKey == CardKeys::Hex1)
			{
				std::vector<Card*> hordeCards = std::vector<Card*>();

				selfDeck->removeCardsWhere([&](Card* card)
				{
					if (card->cardData->cardKey == CardKeys::Hex1)
					{
						hordeCards.push_back(card);
						return true;
					}

					return false;
				});

				selfHand->removeCardsWhere([&](Card* card)
				{
					if (card->cardData->cardKey == CardKeys::Hex1)
					{
						hordeCards.push_back(card);
						return true;
					}

					return false;
				});

				gameState->selectedRow->insertCards(hordeCards, Config::insertDelay);
			}

			SoundManager::playSoundResource(SoundResources::Hexus_CardMovement);
			break;
		}
		case CardData::CardType::Special_ABSORB:
		{
			if (gameState->selectedRow == nullptr)
			{
				this->passFromError(gameState);
				return;
			}

			selfHand->removeCard(gameState->selectedHandCard);
			gameState->selectedRow->insertCard(gameState->selectedHandCard, Config::insertDelay);
			SoundManager::playSoundResource(SoundResources::Hexus_CardMovement);
			break;
		}
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		{
			if (gameState->selectedRow == nullptr)
			{
				this->passFromError(gameState);
				return;
			}

			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			if (!tryAbsorb(gameState, gameState->selectedRow))
			{	
				int index = 0;

				for (auto it = gameState->selectedRow->rowCards.begin(); it != gameState->selectedRow->rowCards.end(); it++, index++)
				{
					Card* card = *it;

					Card::Operation operation = gameState->selectedHandCard->toOperation(card->cardData->getIntrinsicImmediate());

					int previousValue = card->getAttack();

					card->addOperation(operation);

					if (operation.operationType == Card::Operation::OperationType::SHL)
					{
						if (card->getAttack() < previousValue)
						{
							// Run overflow effect, interlacing odd/even offsets to prevent text overlap
							card->runOverflowEffect(index % 2 == 1);
						}
					}
				}

				// Decide which effect and sounds to play
				switch (gameState->selectedHandCard->cardData->cardType)
				{
					case CardData::CardType::Special_SHL:
					{
						gameState->selectedRow->runEffect(CardEffects::CardEffect::MeteorPurple);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_GlitterSpell);
						break;
					}
					case CardData::CardType::Special_SHR:
					{
						gameState->selectedRow->runEffect(CardEffects::CardEffect::MeteorBlue);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_Downgrade);
						break;
					}
					case CardData::CardType::Special_FLIP1:
					{
						gameState->selectedRow->runEffect(CardEffects::CardEffect::TargetPulse);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_MagicSlash);
						break;
					}
					case CardData::CardType::Special_FLIP2:
					{
						gameState->selectedRow->runEffect(CardEffects::CardEffect::FrostCirlce);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_Freeze);
						break;
					}
					case CardData::CardType::Special_FLIP3:
					{
						gameState->selectedRow->runEffect(CardEffects::CardEffect::RadialGalaxy);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_WindReverse);
						break;
					}
					case CardData::CardType::Special_FLIP4:
					{
						gameState->selectedRow->runEffect(CardEffects::CardEffect::RadialFire);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_BurningStrong);
						break;
					}
					default:
					{
						break;
					}
				}
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
			if (gameState->selectedSourceCard == nullptr || gameState->selectedDestinationCard == nullptr)
			{
				this->passFromError(gameState);
				return;
			}

			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			if (!tryAbsorb(gameState, gameState->getRowForCard(gameState->selectedDestinationCard)))
			{
				Card::Operation operation = gameState->selectedHandCard->toOperation(
					gameState->selectedSourceCard->getAttack()
				);

				int previousValue = gameState->selectedDestinationCard->getAttack();

				gameState->selectedDestinationCard->addOperation(operation);

				if (operation.operationType == Card::Operation::OperationType::ADD)
				{
					if (gameState->selectedDestinationCard->getAttack() < previousValue)
					{
						gameState->selectedDestinationCard->runOverflowEffect();
					}
				}
				else if (operation.operationType == Card::Operation::OperationType::SUB)
				{
					if (gameState->selectedDestinationCard->getAttack() > previousValue)
					{
						gameState->selectedDestinationCard->runUnderflowEffect();
					}
				} 

				// Decide which effect and sounds to play
				switch (gameState->selectedHandCard->cardData->cardType)
				{
					case CardData::CardType::Special_MOV:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::DustPoof);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_Shimmer);
						break;
					}
					case CardData::CardType::Special_AND:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::FireBlast);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_Burning);
						break;
					}
					case CardData::CardType::Special_OR:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::Lightning);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_Energy);
						break;
					}
					case CardData::CardType::Special_XOR:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::RadialStorm);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_GenericSpell);
						break;
					}
					case CardData::CardType::Special_ADD:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::MagicBurst);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_ChimeShimmer);
						break;
					}
					case CardData::CardType::Special_SUB:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::StarHit);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_AcidHit);
						break;
					}
					default:
					{
						break;
					}
				}
			}

			break;
		}
		case CardData::CardType::Special_ROL:
		case CardData::CardType::Special_ROR:
		case CardData::CardType::Special_NOT:
		{
			if (gameState->selectedDestinationCard == nullptr)
			{
				this->passFromError(gameState);
				return;
			}

			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			if (!tryAbsorb(gameState, gameState->getRowForCard(gameState->selectedDestinationCard)))
			{
				Card::Operation operation = gameState->selectedHandCard->toOperation(
					gameState->selectedDestinationCard->getAttack()
				);

				gameState->selectedDestinationCard->addOperation(operation);
				
				switch (gameState->selectedHandCard->cardData->cardType)
				{
					case CardData::CardType::Special_ROL:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::StarBurst);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_DemonWhisper);
						break;
					}
					case CardData::CardType::Special_ROR:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::StarHit);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_DemonWhisper);
						break;
					}
					case CardData::CardType::Special_NOT:
					{
						gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::Bite);
						SoundManager::playSoundResource(SoundResources::Hexus_Attacks_DemonWhisper);
						break;
					}
					default:
					{
						break;
					}
				}
			}

			break;
		}
		case CardData::CardType::Special_GREED:
		{
			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			selfHand->insertCard(selfDeck->drawCard(), gameState->turn == GameState::Turn::Player ? Config::insertDelay : 0.0f);
			selfHand->insertCard(selfDeck->drawCard(), gameState->turn == GameState::Turn::Player ? Config::insertDelay : 0.0f);

			break;
		}
		case CardData::CardType::Special_BONUS_MOVES:
		{
			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);
			
			gameState->playableCardsThisTurn += 3;
			break;
		}
		case CardData::CardType::Special_PEEK:
		{
			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			playedPeekCard = true;
			break;
		}
		case CardData::CardType::Special_SUDDEN_DEATH:
		{
			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			auto removeWeakCards = [=](CardRow* targetRow, Deck* targetGraveyard)
			{
				if (!tryAbsorb(gameState, targetRow))
				{
					std::vector<Card*> toRemove = std::vector<Card*>();

					for (auto it = targetRow->rowCards.begin(); it != targetRow->rowCards.end(); it++)
					{
						if ((*it)->cardData->cardKey != CardKeys::Binary0 && (*it)->getAttack() < (*it)->getOriginalAttack())
						{
							toRemove.push_back(*it);
						}
					}

					for (auto it = toRemove.begin(); it != toRemove.end(); it++)
					{
						targetGraveyard->insertCardTop(targetRow->removeCard(*it), true, Config::insertDelay);
					}
				}
			};

			removeWeakCards(selfBinaryRow, selfGraveyard);
			removeWeakCards(selfDecimalRow, selfGraveyard);
			removeWeakCards(selfHexRow, selfGraveyard);
			removeWeakCards(otherBinaryRow, otherGraveyard);
			removeWeakCards(otherDecimalRow, otherGraveyard);
			removeWeakCards(otherHexRow, otherGraveyard);

			break;
		}
		case CardData::CardType::Special_KILL:
		{
			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			CardRow* targetRow = gameState->getRowForCard(gameState->selectedDestinationCard);

			if (targetRow == nullptr)
			{
				this->passFromError(gameState);
				return;
			}

			if (!tryAbsorb(gameState, targetRow))
			{
				if (gameState->selectedDestinationCard->cardData->cardKey != CardKeys::Binary0)
				{
					if (targetRow->isPlayerRow())
					{
						gameState->playerGraveyard->insertCardTop(targetRow->removeCard(gameState->selectedDestinationCard), true, Config::insertDelay);
					}
					else
					{
						gameState->enemyGraveyard->insertCardTop(targetRow->removeCard(gameState->selectedDestinationCard), true, Config::insertDelay);
					}

					gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::Bite);
					SoundManager::playSoundResource(SoundResources::Hexus_Attacks_DemonWhisper);
				}
				else
				{
					// TODO: Failure sound for unsucessful kill attempt
				}
			}

			break;
		}
		case CardData::CardType::Special_RETURN_TO_HAND:
		{
			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			CardRow* targetRow = gameState->getRowForCard(gameState->selectedDestinationCard);

			if (targetRow == nullptr)
			{
				this->passFromError(gameState);
				return;
			}

			if (!tryAbsorb(gameState, targetRow))
			{
				if (gameState->selectedDestinationCard->getIsPlayerOwnedCard())
				{
					gameState->playerHand->insertCard(targetRow->removeCard(gameState->selectedDestinationCard), Config::insertDelay);
				}
				else
				{
					gameState->enemyHand->insertCard(targetRow->removeCard(gameState->selectedDestinationCard), Config::insertDelay);
				}

				gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::DustPoof);
				SoundManager::playSoundResource(SoundResources::Hexus_Attacks_Shimmer);
			}

			break;
		}
		case CardData::CardType::Special_STEAL:
		{
			selfHand->removeCard(gameState->selectedHandCard);
			selfGraveyard->insertCardTop(gameState->selectedHandCard, true, Config::insertDelay);

			CardRow* targetRow = gameState->getRowForCard(gameState->selectedDestinationCard);

			if (targetRow == nullptr)
			{
				this->passFromError(gameState);
				return;
			}

			if (!tryAbsorb(gameState, targetRow))
			{
				auto tryStealCard = [=](CardRow* sourceRow, CardRow* destRow, Card* targetCard)
				{
					destRow->insertCard(sourceRow->removeCard(targetCard), Config::insertDelay);
				};

				tryStealCard(selfBinaryRow, otherBinaryRow, gameState->selectedDestinationCard);
				tryStealCard(selfDecimalRow, otherDecimalRow, gameState->selectedDestinationCard);
				tryStealCard(selfHexRow, otherHexRow, gameState->selectedDestinationCard);
				tryStealCard(otherBinaryRow, selfBinaryRow, gameState->selectedDestinationCard);
				tryStealCard(otherDecimalRow, selfDecimalRow, gameState->selectedDestinationCard);
				tryStealCard(otherHexRow, selfHexRow, gameState->selectedDestinationCard);

				gameState->selectedDestinationCard->cardEffects->runEffect(CardEffects::CardEffect::DustPoof);
				SoundManager::playSoundResource(SoundResources::Hexus_Attacks_Shimmer);
			}

			break;
		}
		default:
		{
			this->passFromError(gameState);
			return;
		}
	}

	gameState->playableCardsThisTurn = std::max(0, gameState->playableCardsThisTurn - 1);

	StatePlayCard::DoNextTransition(gameState, playedPeekCard);
}

void StatePlayCard::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StatePlayCard::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);

	gameState->selectedSourceCard = nullptr;
	gameState->selectedDestinationCard = nullptr;
}

void StatePlayCard::DoNextTransition(GameState* gameState, bool enterPeekState)
{
	gameState->selectedHandCard = nullptr;
	CallFunc* stateTransition = nullptr;

	if (gameState->turn == GameState::Turn::Player)
	{
		if (enterPeekState)
		{
			// Note this case is not covered for the opponent. Considering this into the AI is too much work.
			stateTransition = CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::PeekCards);
			});
		}
		else if (gameState->playerHand->getCardCount() <= 0)
		{
			stateTransition = CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::Pass);
			});
		}
		else
		{
			if (!gameState->playerPassed && !gameState->enemyPassed && gameState->playableCardsThisTurn <= 0)
			{
				stateTransition = CallFunc::create([=]()
				{
					GameState::updateState(gameState, GameState::StateType::TurnEnd);
				});
			}
			else
			{
				stateTransition = CallFunc::create([=]()
				{
					GameState::updateState(gameState, GameState::StateType::Neutral);
				});
			}
		}
	}
	else
	{
		if (gameState->enemyHand->getCardCount() <= 0)
		{
			stateTransition = CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::Pass);
			});
		}
		else
		{
			if (!gameState->playerPassed && !gameState->enemyPassed && gameState->playableCardsThisTurn <= 0)
			{
				stateTransition = CallFunc::create([=]()
				{
					GameState::updateState(gameState, GameState::StateType::TurnEnd);
				});
			}
			else
			{
				stateTransition = CallFunc::create([=]()
				{
					GameState::updateState(gameState, GameState::StateType::AIDecidePass);
				});
			}
		}
	}

	gameState->runAction(Sequence::create(
		DelayTime::create(0.5f),
		stateTransition,
		nullptr
	));
}

void StatePlayCard::passFromError(GameState* gameState)
{
	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::Pass);
		}),
		nullptr
	));
}

bool StatePlayCard::tryAbsorb(GameState* gameState, CardRow* cardRow)
{
	if (cardRow == nullptr)
	{
		return false;
	}

	if (cardRow->isPlayerRow() && gameState->turn == GameState::Turn::Player)
	{
		return false;
	}

	if (!cardRow->isPlayerRow() && gameState->turn == GameState::Turn::Enemy)
	{
		return false;
	}

	for (auto it = cardRow->rowCards.begin(); it != cardRow->rowCards.end(); it++)
	{
		if ((*it)->cardData->cardType == CardData::CardType::Special_ABSORB)
		{
			if (cardRow->isPlayerRow())
			{
				gameState->playerGraveyard->insertCardTop(cardRow->removeCard(*it), true, Config::insertDelay);
			}
			else
			{
				gameState->enemyGraveyard->insertCardTop(cardRow->removeCard(*it), true, Config::insertDelay);
			}

			SoundManager::playSoundResource(SoundResources::Hexus_Attacks_Sheep);
			
			return true;
		}
	}

	return false;
}
