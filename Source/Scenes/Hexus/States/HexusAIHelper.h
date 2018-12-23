#pragma once
#include <tuple>

class Card;
class CardRow;
class GameState;

class HexusAIHelper
{
public:
	static std::tuple<CardRow*, int> getBestRow(Card* candidateCardToPlay, GameState* gameState);
	static std::tuple<Card*, Card*, int> getBestSourceAndTarget(Card* candidateCardToPlay, GameState* gameState);
	static std::tuple<Card*, int> getBestTarget(Card* candidateCardToPlay, GameState* gameState);
};
