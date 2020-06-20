#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

namespace cocos2d
{
	class Node;
}

class Card;
class CardData;
class GameState;
class HexusOpponentData;
class PlatformerEntity;

class HexusEvents
{
public:
	static const std::string EventOpenHexus;
	static const std::string EventExitHexus;
	static const std::string EventShowHelpMenuOutsideOfGame;
	static const std::string EventCardPreviewed;
	static const std::string EventCardMousedOut;
	static const std::string EventBeforeRequestStateUpdate;
	static const std::string EventRequestStateUpdate;
	static const std::string EventBeforeStateUpdate;
	static const std::string EventOnStateUpdate;

	struct HexusOpenArgs
	{
		HexusOpponentData* opponentData;

		HexusOpenArgs(HexusOpponentData* opponentData) : opponentData(opponentData) { }
	};

	struct HexusExitArgs
	{
		HexusExitArgs() { }
	};

	struct CardPreviewArgs
	{
		Card* card;

		CardPreviewArgs(Card* card) : card(card)
		{
		}
	};

	struct HelpMenuArgs
	{
		CardData* cardData;
		std::function<void()> onExit;

		HelpMenuArgs(CardData* cardData, std::function<void()> onExit) : cardData(cardData), onExit(onExit)
		{
		}
	};

	static void TriggerOpenHexus(HexusOpenArgs args);
	static void TriggerExitHexus(HexusExitArgs args);
	static void TriggerShowHelpMenuOutsideOfGame(HelpMenuArgs args);
	static void TriggerCardPreviewed(CardPreviewArgs args);
	static void TriggerCardMousedOut();
	static void TriggerBeforeRequestStateUpdate(GameState* gameState);
	static void TriggerRequestStateUpdate(GameState* gameState);
	static void TriggerBeforeStateUpdate(GameState* gameState);
	static void TriggerOnStateUpdate(GameState* gameState);
	static cocos2d::Node* BuildPreviewNode(PlatformerEntity* entity);
};
