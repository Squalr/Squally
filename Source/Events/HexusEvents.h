#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

class Card;
class GameState;
class HexusOpponentData;
class PlatformerEntity;

class HexusEvents
{
public:
	static const std::string EventOpenHexus;
	static const std::string EventExitHexus;
	static const std::string EventCardPreviewed;
	static const std::string EventCardMousedOut;
	static const std::string BeforeRequestStateUpdateEvent;
	static const std::string RequestStateUpdateEvent;
	static const std::string BeforeStateUpdateEvent;
	static const std::string OnStateUpdateEvent;

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

	static void TriggerOpenHexus(HexusOpenArgs args);
	static void TriggerExitHexus(HexusExitArgs args);
	static void TriggerCardPreviewed(CardPreviewArgs args);
	static void TriggerCardMousedOut();
	static void TriggerBeforeRequestStateUpdate(GameState* gameState);
	static void TriggerRequestStateUpdate(GameState* gameState);
	static void TriggerBeforeStateUpdate(GameState* gameState);
	static void TriggerOnStateUpdate(GameState* gameState);
	static cocos2d::Node* BuildPreviewNode(PlatformerEntity* entity);
};
