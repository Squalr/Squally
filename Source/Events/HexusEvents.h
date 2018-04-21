#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/Hexium.h"

using namespace cocos2d;

// Forward declarations
class Hexium;

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
