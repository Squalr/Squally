#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Minigames/Hexus/Hexus.h"

using namespace cocos2d;

// Forward declarations
class Deck;
class Hexus;

class HexusEvents
{
public:
	static const std::string HexusGameStartEvent;

	struct HexusGameEventArgs
	{
		Deck* playerDeck;
		Deck* enemyDeck;

		HexusGameEventArgs(Deck* playerDeck, Deck* enemyDeck) : playerDeck(playerDeck), enemyDeck(enemyDeck)
		{
		}
	};

	static void startGame(HexusGameEventArgs args);
};
